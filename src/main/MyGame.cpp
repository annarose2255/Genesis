#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Sprite.h"
#include "Scene.h"
#include "MyGame.h"
#include "Sound.h"

using namespace std;

MyGame::MyGame() : Game(1200, 1000) {
	instance = this;

	scene1 = new Scene(); 
	scene1->loadScene("././resources/newsolarsystem.json");
	
	scene2 = new Scene(); 
	scene2->loadScene("././resources/character.json");
	
	currentScene = scene1; 
	instance -> addChild(currentScene);

	//Sound 
	mainMusic = new Sound();

	
}

MyGame::~MyGame(){
}


void MyGame::update(set<SDL_Scancode> pressedKeys){
	
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
		// allSprites->position.x += 2; 
		currentScene->root->position.x += 2; 
	}
	if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
		currentScene->root->position.x -= 2;
	}
	if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
		currentScene->root->position.y += 2;
	}
	if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
		currentScene->root->position.y -= 2;
	}
	if (pressedKeys.find(SDL_SCANCODE_A) != pressedKeys.end()) {
		// sun->rotation += 0.01;
		p1container->rotation += 0.05;
		p2container->rotation += 0.03;
		planet1->rotation += 0.1;
		p1container->position.x = 100*sin(p1container->rotation);
		p2container->position.x = 100*sin(p2container->rotation);
	}
	if (pressedKeys.find(SDL_SCANCODE_S) != pressedKeys.end()) {
		// sun->rotation -= 0.01;
		p1container->rotation -= 0.05;
		p2container->rotation -= 0.03;
		planet1->rotation -= 0.1;
		p1container->position.x = 100*sin(p1container->rotation);
		p2container->position.x = 100*sin(p2container->rotation);
	}
	if (pressedKeys.find(SDL_SCANCODE_Q) != pressedKeys.end()) {
		currentScene->root->scaleX *= 1.05;
		currentScene->root->scaleY *= 1.05;
	}
	if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end()) {
		currentScene->root->scaleX *= 1/1.05;
		currentScene->root->scaleY *= 1/1.05;
	}
	if (pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end()) {
		// sun->play("Sun"); 
		count++;
		a = !a;
		// currentScene = NULL;
		pressedKeys.erase(SDL_SCANCODE_P);
	}
	if (a == true) {
			// cout << " switch to SCENE 2" << endl;
			currentScene = scene2;
			// allSprites->addChild(scene2); 
		}
	else if(a == false ) {
		// cout << "SCENE 2" << endl;
		// cout << "switch to SCENE 1" << endl;
		currentScene = scene1;
	}

	if (pressedKeys.find(SDL_SCANCODE_L) != pressedKeys.end()) {
		sun->stop();
	}

	Game::update(pressedKeys);
	currentScene->update(pressedKeys);

}

void MyGame::draw(AffineTransform &at){
	// cout<<"frame: " <<this ->frameCounter<<endl;
	Game::draw(at);
	SDL_RenderClear(Game::renderer);
    currentScene->draw(at);
    SDL_RenderPresent(Game::renderer);
}
