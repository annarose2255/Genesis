#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Sprite.h"
#include "Scene.h"
#include "MyGame.h"
#include "Camera.h"

using namespace std;

MyGame::MyGame() : Game(800, 700) { //rendered space
	instance = this;
	cam = new Camera();

	scene1 = new Scene(); 
	scene1->loadScene("./resources/scenes/solarsystem.json");

    scene2 = new Scene();
    scene2->loadScene("./resources/scenes/character.json");
	
    change = true;

    currentScene = scene1;

	cam->addChild(currentScene);
    instance->addChild(cam);

    //Sound 
	mainMusic = new Sound();

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

    if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
		currentScene->root->position.x +=2;
		cam->position.x-=2;
		//for camera demo, only move the girl  

	}
	if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
		currentScene->root->position.x -=2; 
		cam->position.x+=2;
	}
	if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
		currentScene->root->position.y +=2; 
		cam->position.y-=2;
	
	}
	if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
		currentScene->root->position.y -=2; 
		cam->position.y+=2;
	}


    cam->camera.x =  currentScene->position.x +  currentScene->width/2 - 400;
	cam->camera.y =  currentScene->position.y +  currentScene->height/2 - 350;
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
	Game::update(pressedKeys);
	// currentScene->doCam = cam->camera;
}

void MyGame::draw(AffineTransform &at, SDL_Rect camera){
	// camera = cam->camera;
	//Order -> Game -> Affine -> DisplayObject -> myGame
	Game::draw(at, cam->camera);
	SDL_RenderSetViewport(Game::renderer, &cam->camera );
}

