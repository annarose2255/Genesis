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
	scene1->loadScene("./resources/scenes/solarsystem.json");
    instance->addChild(scene1);
    scene1->visible = false;

    scene2 = new Scene();
    scene2->loadScene("./resources/scenes/character.json");
    scene2->visible = false;
	//scene2 = new Scene(); 
	//scene2->loadScene("././resources/character.json");
	
	//currentScene = scene2; 
	//instance -> addChild(currentScene);
	
}

MyGame::~MyGame(){
}


void MyGame::update(set<SDL_Scancode> pressedKeys){
    
    if(pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end()) {
        scene1->visible = false;
        scene2->visible = true;
        cout << "aaaaaa" << endl;
    }

	Game::update(pressedKeys);
}

void MyGame::draw(AffineTransform &at){
	Game::draw(at);
}

