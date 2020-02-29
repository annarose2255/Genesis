#ifndef MYGAME_H
#define MYGAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Game.h"
#include "Sprite.h"
#include "Sound.h"
#include "AnimatedSprite.h"
#include "Scene.h"
#include "Camera.h"

using namespace std;

class MyGame : public Game{

public:
	MyGame();
	virtual ~MyGame();

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &, SDL_Rect camera);
    Scene* currentScene;
    static SDL_Rect camera;

private:
    Sound* mainMusic;
    
    bool change;    
    Scene* scene1;
    Scene* scene2;    	

    Camera* cam;
};

#endif
