#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Sprite.h"
#include "Scene.h"
#include "MyGame.h"
#include "Camera.h"
#include "QuestDemo.h"
#include "QuestManager.h"
#include "Tween.h"
#include "TweenableParams.h"
#include "TweenEvent.h"

using namespace std;

MyGame::MyGame() : Game(800, 700) { //rendered space
	instance = this;
	cam = new Camera();

	// scene1 = new Scene(); 
	// scene1->loadScene("./resources/scenes/solarsystem.json");

    scene2 = new Scene();
    scene2->loadScene("./resources/scenes/character.json");
	//questComplete = new DisplayObjectContainer("quest complete", "./resources/quest/questComplete.png"); //not visible yet
    change = true;
    currentScene = scene2;

	//Camera
	cam->addChild(currentScene);
    instance->addChild(cam);

    //Sound 
	mainMusic = new Sound();

	//QuestDemo
	eDispatcher = new EventDispatcher();
	cout << "up to dispatcher" << endl;
	coinlis = new CoinListener(scene2->asList.at(0), scene2->objects.at(0));
	cout << "we good" << endl;
	myQuestManager = new QuestManager(scene2->objects.at(1));
	eDispatcher->addEventListener(coinlis, PICKUP);
	eDispatcher->addEventListener(myQuestManager, COLLECTED);

	//Tween
	Tween* charTween = new Tween(scene2->asList.at(0));
	charTween->animate("alpha", 2, 1, 3); //have not implemented yet :')
	// TweenEvent te = new TweenEvent("enterChara", charTween); //handle events 
	// TweenJuggler tj = new TweenJuggler();
	// tj.add(charTween);

}

MyGame::~MyGame(){
}


void MyGame::update(set<SDL_Scancode> pressedKeys){

    if(pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end() && change) {
        cout << "abc" << endl;
        cam->removeImmediateChild(currentScene);
        cout << instance->children.size() << endl;
        currentScene = scene2;
        cam->addChild(currentScene);
        change = !change;
    }
    else if(pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end() && !change) {
        cout << "123" << endl;
        cam->removeImmediateChild(currentScene);
        currentScene = scene1;
        cam->addChild(currentScene);
        change = !change;
    }

    //for music - press1 and the music will play
	//user press 1 --> play music
	if ((pressedKeys.find(SDL_SCANCODE_1) != pressedKeys.end())) {
		cout<<"playing?"<<endl;
		mainMusic->playMusic();
		
	}
    
	//user press2 --> stop music
    if ((pressedKeys.find(SDL_SCANCODE_2) != pressedKeys.end())) {
		cout<<"pause playing"<<endl;
		mainMusic->pauseMusic();
		
	}
	//changing position of camera
    if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
		currentScene->asList.at(0)->position.x += 3; //change this to reference layer instead
		currentScene->position.x-=2;

	}
	if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
		currentScene->asList.at(0)->position.x -=3; 
		currentScene->position.x+=2;
	}
	if (currentScene->position.y-2 > 106) { //change to check a specific layer
		if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
			currentScene->asList.at(0)->position.y +=2; 
			currentScene->position.y-=2;
		}
	} 
	
	if ((currentScene->position.y <= cam->camera.h) ){
		if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
			currentScene->asList.at(0)->position.y -=2; 
			currentScene->position.y+=2;
		}
	}
	//character moves separately from scene
	if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end()) {
		currentScene->asList.at(0)->position.y -=2; 
	}
	if (pressedKeys.find(SDL_SCANCODE_S) != pressedKeys.end()) {
		currentScene->asList.at(0)->position.y +=2; 
	}
	if (pressedKeys.find(SDL_SCANCODE_A) != pressedKeys.end()) {
		currentScene->asList.at(0)->position.x -=2; 
	}
	if (pressedKeys.find(SDL_SCANCODE_D) != pressedKeys.end()) {
		currentScene->asList.at(0)->position.x +=2; 
	}



    cam->camera.x =  currentScene->position.x +  currentScene->width/2 - 400;
	cam->camera.y =  currentScene->position.y +  currentScene->height/2 - 350;
	cout << "Cam x " << cam->camera.x << endl; 
	cout << "Cam y " << cam->camera.y << endl;
	cout << "Scene x " << currentScene->position.x << endl; 
	cout << "Scene y " << currentScene->position.y << endl; 
	if( cam->camera.x < 0){
		cam->camera.x = 0;
	}
    if( cam->camera.y < 0 ){
		cam->camera.y = 0;
    }
	if (cam->camera.x > cam->camera.w){
		cam->camera.x = cam->camera.w;
	}
	if (cam->camera.y > cam->camera.h) {
		cam->camera.y = cam->camera.h;
	}
	if (currentScene->objects.size() > 0) {
		cout << "objects exist" << endl;
		if (currentScene->objects.at(0)->visible && isCharInCoin(currentScene->asList.at(0), currentScene->objects.at(0))) {
			eDispatcher->dispatchEvent(new Event(PICKUP, eDispatcher));
			// currentScene->addChild(questComplete);
    	}
		if (!currentScene->objects.at(0)->visible && isOngoing)
		{
			cout << "collected event" << endl;
			isOngoing = false;
			eDispatcher->dispatchEvent(new Event(COLLECTED, eDispatcher));
		}
	}
	Game::update(pressedKeys);
	// currentScene->doCam = cam->camera;
}

void MyGame::draw(AffineTransform &at, SDL_Rect camera){
	Game::draw(at, cam->camera); 
	SDL_RenderSetViewport(Game::renderer, &cam->camera );
}

bool MyGame::isCharInCoin(DisplayObject* chara, DisplayObject* cn) {
    SDL_Point* charPos, charTemp;
    SDL_Rect* cnRect, cnTemp;
    charTemp = {chara->position.x + chara->pivot.x, chara->position.y + chara->pivot.y};
    charPos = &charTemp;
    cnTemp = {cn->position.x, cn->position.y, cn->width, cn->height};
    cnRect = &cnTemp;
    return SDL_PointInRect(charPos, cnRect);
}


