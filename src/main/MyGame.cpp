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
#include "TweenJuggler.h"

using namespace std;

MyGame::MyGame() : Game(800, 700) { //rendered space
	instance = this;
    scene1 = new Scene();
    // scene2->loadScene("./resources/scenes/character.json");
	scene1->loadTileMap("./resources/scenes/area 1 files/tsx files/Area 1 - Room 7.tmx", false);
	scene2 = new Scene();
	scene2->loadTileMap("./resources/scenes/area 1 files/tsx files/Area 1 - Room 5.tmx", true);

    change = true;
    currentScene = scene1;

	Game::camera->addChild(currentScene);
	instance->addChild(Game::camera);

    //Sound 
	mainMusic = new Sound();

	//Change Scene 
	sm = new SceneManager(currentScene->getCharacter(), currentScene);
	eDispatcher = new EventDispatcher();
	eDispatcher->addEventListener(sm, CHANGE);
	//QuestDemo
	// eDispatcher = new EventDispatcher();
	// // cout << "up to dispatcher" << endl;
	// coinlis = new CoinListener(scene2->asList.at(0), scene2->objects.at(0));
	// // cout << "we good" << endl;
	// myQuestManager = new QuestManager(scene2->objects.at(1));
	// eDispatcher->addEventListener(coinlis, PICKUP);
	// eDispatcher->addEventListener(myQuestManager, COLLECTED);

	//Tween
	// TweenJuggler* tj = new TweenJuggler();
	// Tween* charTween = new Tween(scene2->asList.at(0));
	// TweenableParams px;
	// TweenableParams py; 
	// px.name = "position.x";
	// py.name = "position.y";
	// charTween->animate(px, 0, 300, 30); //have not implemented yet :')
	// charTween->animate(py, 700, 300, 30);
	// // TweenEvent te = new TweenEvent("enterChara", charTween); //handle events 
	// //mimic coin demo
	// tj->add(charTween);

}

MyGame::~MyGame(){
}


void MyGame::update(set<SDL_Scancode> pressedKeys){

    if(pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end() && change) {
        cout << "abc" << endl;
        Game::camera->removeImmediateChild(currentScene);
        cout << instance->children.size() << endl;
        currentScene = scene2;
        Game::camera->addChild(currentScene);
        change = !change;
    }
    else if(pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end() && !change) {
        cout << "123" << endl;
       	Game::camera->removeImmediateChild(currentScene);
        currentScene = scene1;
        Game::camera->addChild(currentScene);
        change = !change;
    }
	if ((pressedKeys.find(SDL_SCANCODE_Z) != pressedKeys.end())) {
		currentScene->scaleX+=0.01; 
		currentScene->scaleY+=0.01;
	}
	if ((pressedKeys.find(SDL_SCANCODE_X) != pressedKeys.end())) {
		currentScene->scaleY-=0.01;
		currentScene->scaleX-=0.01;
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

	//changing position of scene
	if (currentScene->position.x-5 > -2105) {
		if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
			// Game::camera->position.x-=5;
			currentScene->position.x-=5;
		}
	}
	if (currentScene->position.x+5 < 0) {
		if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
			// Game::camera->position.x+=5;
			currentScene->position.x+=5;
		}
	}
	if (currentScene->position.y-5 > -180) {
		if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
			// Game::camera->position.y-=5;
			currentScene->position.y-=5;
		}
	}	
	if (currentScene->position.y+5 < -5){
		if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
			// Game::camera->position.y+=5;
			currentScene->position.y+=5;
		}
	}

	//character moves separately from scene
	if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end()) {
		currentScene->getCharacter()->position.y -=2;
	}
	if (pressedKeys.find(SDL_SCANCODE_S) != pressedKeys.end()) {
		currentScene->getCharacter()->position.y +=2;
	}
	if (pressedKeys.find(SDL_SCANCODE_A) != pressedKeys.end()) {
		currentScene->getCharacter()->facingRight = false;
		currentScene->getCharacter()->position.x -=2;
			// currentScene->position.x+=2; //comment out to just move sprite
	}
	if (pressedKeys.find(SDL_SCANCODE_D) != pressedKeys.end()) {
		currentScene->getCharacter()->facingRight = true;
		currentScene->getCharacter()->position.x +=2; 
			// currentScene->position.x-=2; //comment out to just move sprite
	}
	//updating camera position
    Game::camera->camera.x =  currentScene->position.x +  currentScene->width/2 - 400;
	Game::camera->camera.y =  currentScene->position.y +  currentScene->height/2 - 350;
	cout << "Scene x " << currentScene->position.x << endl; 
	cout << "Scene y " << currentScene->position.y << endl; 
	// cout << "Character x " << currentScene->getCharacter()->position.x << endl;
	// cout << "Character y " << currentScene->getCharacter()->position.y << endl;
	if( Game::camera->camera.x < 0){
		Game::camera->camera.x = 0;
	}
    if( Game::camera->camera.y < 0 ){
		Game::camera->camera.y = 0;
    }
	if (Game::camera->camera.x > Game::camera->camera.w){
		Game::camera->camera.x = Game::camera->camera.w;
	}
	if (Game::camera->camera.y > Game::camera->camera.h) {
		Game::camera->camera.y = Game::camera->camera.h;
	}
	//Quest Demo stuff
	// if (currentScene->objects.size() > 0) {
	// 	// cout << "objects exist" << endl;
	// 	if (currentScene->objects.at(0)->visible && isCharInCoin(currentScene->asList.at(0), currentScene->objects.at(0))) {
	// 		eDispatcher->dispatchEvent(new Event(PICKUP, eDispatcher));
	// 		// currentScene->addChild(questComplete);
    // 	}
	// 	if (!currentScene->objects.at(0)->visible && isOngoing)
	// 	{
	// 		// cout << "collected event" << endl;
	// 		isOngoing = false;
	// 		eDispatcher->dispatchEvent(new Event(COLLECTED, eDispatcher, currentScene.asList(0),
		//"./resources/scenes/area 1 files/tsx files/Area 1 - Room 5.tmx"));
	// 	}
	// }

	//Change scene 
	if ((currentScene == scene1) && (currentScene->getCharacter()->position.y < 36 && 
		(24 < currentScene->getCharacter()->position.x && currentScene->getCharacter()->position.x < 140))) {
			cout << "exited room!" << endl;
			eDispatcher->dispatchEvent(new Event(CHANGE, eDispatcher, currentScene->getCharacter(), 
				scene2));
			cout << "out of dispatcher" << endl;
			Game::camera->removeImmediateChild(currentScene);
			currentScene = sm->getCurrentScene();        
			Game::camera->addChild(currentScene);
			// Game::camera->addChild(currentScene);
			// Game::camera->removeImmediateChild(currentScene);
	}
	//sm->handleEvent(CHANGE);
	Game::update(pressedKeys);
	// currentScene->doCam = cam->camera;
}

void MyGame::draw(AffineTransform &at){
	Game::draw(at); 
	SDL_RenderSetViewport(Game::renderer, &Game::camera->camera);
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

