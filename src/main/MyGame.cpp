#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Sprite.h"
#include "Scene.h"
#include "MyGame.h"

using namespace std;

MyGame::MyGame() : Game(1200, 1000) {
	instance = this;

	allSprites = new DisplayObjectContainer();
	// move that point to the middle
	allSprites->position = {600, 500};
	instance->addChild(allSprites);
	//currentScene variable
	scene1 = new Scene(); 
	scene1->loadScene("././resources/solarsystem.json");
	sun = scene1->as1.front();
	sun->play("Sun");
	p1container = scene1->doc.front(); 
	p2container = scene1->doc.back();
	planet1 = scene1->s.front();	
	planet2 = scene1->s.at(1);
	moon1_1 = scene1->s.back(); 
	allSprites->addChild(sun);
	scene2 = new Scene(); 
	scene2->loadScene("././resources/character.json");
	character = scene2->s.front();
	currentScene = scene1; 
	//load sun and add child to allSprites scene1->as
	//access the vectors within scene1 to call specific Sprites, AnimatedSprites, and DisplayObjectContainers

}

MyGame::~MyGame(){
}


void MyGame::update(set<SDL_Scancode> pressedKeys){
	if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
		sun->position.x += 2; 
	}
	if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
		sun->position.x -= 2;
	}
	if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
		sun->position.y += 2;
	}
	if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
		sun->position.y -= 2;
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
		allSprites->scaleX *= 1.05;
		allSprites->scaleY *= 1.05;
	}
	if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end()) {
		allSprites->scaleX *= 1/1.05;
		allSprites->scaleY *= 1/1.05;
	}
	if (pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end()) {
		cout << i << " hello" << endl;
		cout << "Num Children " << allSprites->numChildren() << endl;
		cout << "Scene 1 " << scene1 << endl;
		cout << "Scene 2 " << scene2 << endl;
		cout << "current scene " << currentScene << endl;
		// sun->play("Sun");  
		if (allSprites->getChild(0) == sun) {
			cout << "SUN!" << endl;
			currentScene = scene2;
			allSprites->removeImmediateChild(sun);
			allSprites->addChild(character);
			i++; 
		}
		else {
			cout << "CHARACTER!" << endl;
			currentScene = scene1;
			allSprites->removeImmediateChild(character);
			cout << "meh" << endl;
			allSprites->addChild(sun); 
			i++;
		}
	}
	if (pressedKeys.find(SDL_SCANCODE_L) != pressedKeys.end()) {
		sun->stop();
	}
	Game::update(pressedKeys);
}

void MyGame::draw(AffineTransform &at){
	Game::draw(at);

}
