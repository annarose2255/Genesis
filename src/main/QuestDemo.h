#ifndef QUESTDEMO_H
#define QUESTDEMO_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Game.h"
#include "Sprite.h"
#include "AnimatedSprite.h"
#include "CoinListener.h"

using namespace std;

class QuestDemo : public Game{

public:
	QuestDemo();
	virtual ~QuestDemo();

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

private:
	
	AnimatedSprite* coin;
	// Sprite* planet1;
	// Sprite* planet2;
	// Sprite* moon1_1;

	// DisplayObjectContainer* p1container;
	// DisplayObjectContainer* p2container;
	DisplayObjectContainer* allSprites;
	EventListener* coinlis;
	EventDispatcher* eDispatch;
	AnimatedSprite* character;
	bool isWalking = false;
	bool left = false;
	bool isJumping = false;
};

#endif