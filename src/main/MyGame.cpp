#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Scene.h"
#include "MyGame.h"

using namespace std;

MyGame::MyGame() : Game(1200, 1000) {
	Scene* scene1 = new Scene(); 
	scene1->loadScene("./resources/scenes/scene1.json");

	currentScene = scene1;
}

MyGame::~MyGame(){
}


void MyGame::update(set<SDL_Scancode> pressedKeys){

	Game::update(pressedKeys);
	currentScene->update(pressedKeys);
}

void MyGame::draw(AffineTransform &at){
	Game::draw(at);
	currentScene->draw(at);

}