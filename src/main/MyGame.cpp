#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Sprite.h"
#include "Scene.h"
#include "MyGame.h"
#include "Sound.h"

using namespace std;

MyGame::MyGame() : Game(800, 700) {
	instance = this;

	scene1 = new Scene(); 
	scene1->loadScene("././resources/newsolarsystem.json");
	
	scene2 = new Scene(); 
	scene2->loadScene("././resources/character.json");
	
	currentScene = scene2; 
	instance -> addChild(currentScene);

	//Sound 
	mainMusic = new Sound();

	//Camera
	// camera = currentScene->c;
	
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
		// currentScene->CameraPosX += SpeedX;
		// currentScene->root->position.x -= CameraPosX; 
		currentScene->root->position.x += 2; 

		// camera->x = ( currentScene->root->position.x ) - 800 / 2;
		// camera->y = ( currentScene->root->position.y ) - 700 / 2;
	}
	if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
		currentScene->root->position.x -= 2;
		// currentScene->CameraPosX -= SpeedX;
		// camera->x = ( currentScene->root->position.x ) - 800 / 2;
		// camera->y = ( currentScene->root->position.y ) - 700 / 2;
	}
	if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
		currentScene->root->position.y += 2;
		// currentScene->CameraPosY += SpeedY;
		// camera->x = ( currentScene->root->position.x ) - 800 / 2;
		// camera->y = ( currentScene->root->position.y ) - 700 / 2;
	}
	if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
		currentScene->root->position.y -= 2;
		// currentScene->CameraPosY -= SpeedY;
		// camera->x = ( currentScene->root->position.x ) - 800 / 2;
		// camera->y = ( currentScene->root->position.y ) - 700 / 2;
	}
	
	//Camera
	// currentScene->root->position.x -= CameraPosX; 
	// currentScene->root->position.y -= CameraPosY; 
	// currentScene->PlayerPosX = (int)(PlayerPosX - CameraPosX);
	// currentScene->PlayerPosY = (int)(PlayerPosY - CameraPosY);




	if (pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end()) {
		// sun->play("Sun"); 
		count++;
		a = !a;
		trans = true;
		// currentScene = NULL;
		pressedKeys.erase(SDL_SCANCODE_P);
	}
	else if(trans && pressedKeys.size() == 0){
		cout << "Change ScneE" << endl;
		trans = false;
		if (a == true) {
				// cout << " switch to SCENE 2" << endl;
				currentScene = scene2;
				// this -> removeChild(0);
				// this -> addChild(currentScene);
				// allSprites->addChild(scene2); 
			}
		else if(a == false ) {
			// cout << "SCENE 2" << endl;
			// cout << "switch to SCENE 1" << endl;
			currentScene = scene1;
		}
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
