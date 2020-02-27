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

    scene2 = new Scene();
    scene2->loadScene("./resources/scenes/character.json");
	
    change = true;

    currentScene = scene1;
    instance->addChild(currentScene);

    //Sound 
	mainMusic = new Sound();

}

MyGame::~MyGame(){
}


void MyGame::update(set<SDL_Scancode> pressedKeys){

    if(pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end() && change) {
        cout << "abc" << endl;
        instance->removeImmediateChild(currentScene);
        cout << instance->children.size() << endl;
        currentScene = scene2;
        instance->addChild(currentScene);
        change = !change;
    }
    else if(pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end() && !change) {
        cout << "123" << endl;
        instance->removeImmediateChild(currentScene);
        currentScene = scene1;
        instance->addChild(currentScene);
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
    
    if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
		currentScene->position.x += 2; 

	}
	if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
		currentScene->position.x -= 2;
		
	}
	if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
		currentScene->position.y += 2;
	
	}
	if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
		currentScene->position.y -= 2;
	}

	Game::update(pressedKeys);
}

void MyGame::draw(AffineTransform &at){
	Game::draw(at);
}

