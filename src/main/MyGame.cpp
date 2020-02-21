#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Sprite.h"
#include "Scene.h"
#include "MyGame.h"

using namespace std;

MyGame::MyGame() : Game(1200, 1000) {
	instance = this;
	//currentScene child of myGame 
	//currentScene references each scene 
<<<<<<< HEAD
	// allSprites = new DisplayObjectContainer();
	// move that point to the middle
	// allSprites->position = {600, 500};
	// instance->addChild(allSprites);
	//currentScene variable


	scene1 = new Scene(); 
	scene1->loadScene("././resources/solarsystem.json");
	// sun = scene1->as1.front();
	// sun->play("Sun");
	// p1container = scene1->doc.front(); 
	// p2container = scene1->doc.back();
	// planet1 = scene1->s.front();	
	// planet2 = scene1->s.at(1);
	// moon1_1 = scene1->s.back(); 
	
	scene2 = new Scene(); 
	scene2->loadScene("././resources/character.json");
	// character = scene2->as1.front();
	// character->play("Sun");

	currentScene = scene1; 
	instance -> addChild(currentScene);
	
	// currentScene = scene1; 
	// instance -> addChild(currentScene);
	// allSprites -> addChild(currentScene);

	// allSprites->addChild(currentScene);
	
	// allSprites->addChild(sun);
	// allSprites->addChild(character);
	//load sun and add child to allSprites scene1->as
	//access the vectors within scene1 to call specific Sprites, AnimatedSprites, and DisplayObjectContainers

=======
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
	scene2 = new Scene(); 
	scene2->loadScene("././resources/character.json");
	character = scene2->s.front();
	currentScene = scene1; 
	allSprites->addChild(currentScene);
	// allSprites->addChild(sun);
	// allSprites->addChild(character);
	//load sun and add child to allSprites scene1->as
	//access the vectors within scene1 to call specific Sprites, AnimatedSprites, and DisplayObjectContainers

>>>>>>> 58f6041ed11549ce63a02449d051d5b029d95aad
}

MyGame::~MyGame(){
}


void MyGame::update(set<SDL_Scancode> pressedKeys){
	if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
<<<<<<< HEAD
		// allSprites->position.x += 2; 
		currentScene->position.x += 2; 
=======
		sun->position.x += 2; 
>>>>>>> 58f6041ed11549ce63a02449d051d5b029d95aad
	}
	if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
		allSprites->position.x -= 2;
	}
	if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
		allSprites->position.y += 2;
	}
	if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
		allSprites->position.y -= 2;
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
		// sun->play("Sun"); 
<<<<<<< HEAD
		cout<<"pressed"<<endl;
		a = !a;
=======

		cout<<"pressed key command"<<endl; 
		if (currentScene == scene1) {
			cout << "SCENE 1" << endl;
			currentScene = scene2; 
		}
		else {
			cout << "SCENE 2" << endl;
			currentScene = scene1;
		}
>>>>>>> 58f6041ed11549ce63a02449d051d5b029d95aad
	}
	if (a == true) {
			// cout << "SCENE 1" << endl;
			currentScene = scene2;
			// allSprites->addChild(scene2); 
		}
	else if(a == false) {
		// cout << "SCENE 2" << endl;
		currentScene = scene1;
	}

	if (pressedKeys.find(SDL_SCANCODE_L) != pressedKeys.end()) {
		sun->stop();
	}

	Game::update(pressedKeys);
	currentScene->update(pressedKeys);

}

void MyGame::draw(AffineTransform &at){
	cout<<"draw method"<<endl;
	Game::draw(at);
	SDL_RenderClear(Game::renderer);
    currentScene->draw(at);
    SDL_RenderPresent(Game::renderer);
}
