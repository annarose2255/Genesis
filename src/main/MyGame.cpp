#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Sprite.h"
#include "Scene.h"
#include "MyGame.h"

using namespace std;

MyGame::MyGame() : Game(800, 700) {
	instance = this;

	scene1 = new Scene(); 
	scene1->loadScene("./resources/scenes/character2.json");

    scene2 = new Scene();
    scene2->loadScene("./resources/scenes/character.json");
	
    scene3 = new Scene();
    scene3->loadScene("./resources/scenes/solarsystem.json");

    change = true;
    currentScene = scene3;
    instance->addChild(currentScene);
}

MyGame::~MyGame(){
}


void MyGame::update(set<SDL_Scancode> pressedKeys){
    
    if(pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end() && change) {
        cout << "abc" << endl;
        instance->removeImmediateChild(currentScene);
        currentScene = scene3;
        instance->addChild(currentScene);
        change = !change;

    }
    else if(pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end() && !change) {
        cout << "123" << endl;
        instance->removeImmediateChild(currentScene);
        currentScene = scene2;
        instance->addChild(currentScene);
        change = !change;

    }
	Game::update(pressedKeys);
}

void MyGame::draw(AffineTransform &at){
	Game::draw(at);
}

