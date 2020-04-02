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
	// cam = new Camera();

	scene1 = new Scene(); 
	scene1->loadScene("./resources/scenes/solarsystem.json");

    scene2 = new Scene();
    scene2->loadScene("./resources/scenes/character.json");
	//questComplete = new DisplayObjectContainer("quest complete", "./resources/quest/questComplete.png"); //not visible yet
    change = true;
    currentScene = scene2;

	//Camera
	// cam->addChild(currentScene);
    // instance->addChild(cam);

	Game::camera->addChild(currentScene);
	instance->addChild(Game::camera);

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
	TweenableParams px;
	TweenableParams py; 
	px.name = "position.x";
	py.name = "position.y";
	charTween->animate(px, 0, 300, 30); //have not implemented yet :')
	charTween->animate(py, 700, 300, 30);
	// TweenEvent te = new TweenEvent("enterChara", charTween); //handle events 
	// TweenJuggler tj = new TweenJuggler();
	// tj.add(charTween);

}

MyGame::~MyGame(){
}


void MyGame::update(set<SDL_Scancode> pressedKeys, ControllerInput controllerInput){
    
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
	Game::update(pressedKeys, controllerInput);
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

