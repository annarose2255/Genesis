#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Sprite.h"
#include "CollisionDemo.h"
#include "QuestManager.h"
#include "Event.h"
#include "CollisionSystem.h"

using namespace std;

CollisionDemo::CollisionDemo() : Game(1200, 1000) {
	instance = this;
	// init collision system for demo
	collisionSystem = new CollisionSystem();
	// get pointer to event dispatcher
	EventDispatcher* eDispatcher = EventDispatcher::getInstance();
	// register adding display object event  to collision system
	eDispatcher->addEventListener(collisionSystem, DO_ADDED_EVENT);

	allSprites = new DisplayObjectContainer();
	// move that point to the middle
	allSprites->position = {600, 500};
	instance->addChild(allSprites);

	coin = new AnimatedSprite("coin", "./resources/quest/Gold.png", "./resources/quest/Gold.xml");
	coin->play("Gold");
    coin->position = {0, 0};
	//coin->setHitbox({20, 0}, 60, coin->height);
	coin->gameType = "collectable";
	// coin->width = coin->height = 100;
	// coin->pivot = {50, 50};
	questComplete = new DisplayObjectContainer("quest complete", "./resources/quest/questComplete.png");
	questComplete->position = {-200, 0};
	//questComplete->setHitbox({0, 0}, questComplete->width, questComplete->height);
	questComplete->gameType = "not collectable";
	allSprites->addChild(coin);
	allSprites->addChild(questComplete);

	collisionSystem->watchForCollisions("not collectable", "collectable");
	collisionSystem->watchForCollisions("collectable", "not collectable");
}

CollisionDemo::~CollisionDemo(){
}


void CollisionDemo::update(set<SDL_Scancode> pressedKeys, set<SDL_GameControllerButton> pressedButtons, set<pair<SDL_GameControllerAxis, float>> movedAxis){
	
	// all sprites movement
	if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end()) {
		allSprites->position.y -= 3;
	}
	if (pressedKeys.find(SDL_SCANCODE_A) != pressedKeys.end()) {
		allSprites->position.x -= 3;
	}
	if (pressedKeys.find(SDL_SCANCODE_S) != pressedKeys.end()) {
		allSprites->position.y += 3;
	}
	if (pressedKeys.find(SDL_SCANCODE_D) != pressedKeys.end()) {
		allSprites->position.x += 3;
	}

	// rotate
	if (pressedKeys.find(SDL_SCANCODE_E) != pressedKeys.end()) {
		allSprites->rotation += 0.1;
	}
	if (pressedKeys.find(SDL_SCANCODE_R) != pressedKeys.end()) {
		allSprites->rotation -= 0.1;
	}

	// scale
	if (pressedKeys.find(SDL_SCANCODE_F) != pressedKeys.end()) {
		allSprites->scaleX *= 1.05;
		allSprites->scaleY *= 1.05;
	}
	if (pressedKeys.find(SDL_SCANCODE_G) != pressedKeys.end()) {
		allSprites->scaleX *= 1/1.05;
		allSprites->scaleY *= 1/1.05;
	}

	// coin movement
	if (pressedKeys.find(SDL_SCANCODE_I) != pressedKeys.end()) {
		coin->position.y -= 3;
	}
	if (pressedKeys.find(SDL_SCANCODE_J) != pressedKeys.end()) {
		coin->position.x -= 3;
	}
	if (pressedKeys.find(SDL_SCANCODE_K) != pressedKeys.end()) {
		coin->position.y += 3;
	}
	if (pressedKeys.find(SDL_SCANCODE_L) != pressedKeys.end()) {
		coin->position.x += 3;
	}

	// rotate
	if (pressedKeys.find(SDL_SCANCODE_O) != pressedKeys.end()) {
		coin->rotation += 0.1;
	}
	if (pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end()) {
		coin->rotation -= 0.1;
	}

	// scale
	if (pressedKeys.find(SDL_SCANCODE_M) != pressedKeys.end()) {
		coin->scaleX *= 1.05;
		coin->scaleY *= 1.05;
	}
	if (pressedKeys.find(SDL_SCANCODE_N) != pressedKeys.end()) {
		coin->scaleX *= 1/1.05;
		coin->scaleY *= 1/1.05;
	}

	// quest complete movement
	if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
		questComplete->position.y -= 3;
	}
	if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
		questComplete->position.x -= 3;
	}
	if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
		questComplete->position.y += 3;
	}
	if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
		questComplete->position.x += 3;
	}

	// rotate
	if (pressedKeys.find(SDL_SCANCODE_X) != pressedKeys.end()) {
		questComplete->rotation += 0.1;
	}
	if (pressedKeys.find(SDL_SCANCODE_C) != pressedKeys.end()) {
		questComplete->rotation -= 0.1;
	}

	// scale
	if (pressedKeys.find(SDL_SCANCODE_V) != pressedKeys.end()) {
		questComplete->scaleX *= 1.05;
		questComplete->scaleY *= 1.05;
	}
	if (pressedKeys.find(SDL_SCANCODE_B) != pressedKeys.end()) {
		questComplete->scaleX *= 1/1.05;
		questComplete->scaleY *= 1/1.05;
	}

	// if (collisionSystem->collidesWith(questComplete, coin) ) {
	// 	// cout << "COLLISION" << endl;
	// } else {
	// 	// cout << "NO COLLISION" << endl;
	// }
	collisionSystem->update();

	Game::update(pressedKeys, pressedButtons, movedAxis);
}

void CollisionDemo::draw(AffineTransform &at){
	Game::draw(at);
}