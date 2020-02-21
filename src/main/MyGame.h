#ifndef MYGAME_H
#define MYGAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Game.h"
#include "Sprite.h"
#include "Scene.h"
#include "Sound.h"
#include "AnimatedSprite.h"


using namespace std;

class MyGame : public Game{

public:
	int count =0;
	MyGame();
	virtual ~MyGame();

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

private:
	Sound* mainMusic;
	bool a = false;

	AnimatedSprite* sun;
	Sprite* planet1;
	Sprite* planet2;
	Sprite* moon1_1;
	DisplayObjectContainer* p1container;
	DisplayObjectContainer* p2container;
	DisplayObjectContainer* allSprites;

	AnimatedSprite* character;
	Scene* scene1; 
	Scene* scene2; 
	Scene* currentScene;
	int i = 1; 
	// DisplayObject* character;
};

#endif