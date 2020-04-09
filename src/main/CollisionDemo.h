#ifndef COLLISIONDEMO_H
#define COLLISIONDEMO_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Game.h"
#include "Sprite.h"
#include "AnimatedSprite.h"
#include "CoinListener.h"
#include "CollisionSystem.h"

using namespace std;

class CollisionDemo : public Game{

public:
	CollisionDemo();
	virtual ~CollisionDemo();

	virtual void update(set<SDL_Scancode> pressedKeys, set<SDL_GameControllerButton> pressedButtons);
	virtual void draw(AffineTransform &at);

private:

	CollisionSystem* collisionSystem;
	AnimatedSprite* coin;
	DisplayObjectContainer *questComplete;
	DisplayObjectContainer* allSprites;

	// EventListener* coinlis;
	// EventListener* myQuestManager;
	// EventDispatcher* eDispatcher;
	// AnimatedSprite* character;

};

#endif

