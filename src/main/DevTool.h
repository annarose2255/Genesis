#ifndef DEVTOOL_H
#define DEVTOOL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Game.h"
#include "Sprite.h"
#include "AnimatedSprite.h"
#include "Scene.h"

using namespace std;

class DevTool : public Game{

public:
	DevTool();
	virtual ~DevTool();

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

    void load(string filepath);
    void save(string filepath);
    void tileSnap();
    void copy();
    void paste(); 


private:
    
    // Camera* mainCamera;
    bool change;
    Scene* currentScene;    
    Scene* scene1;
    Scene* scene2;    	
    DisplayObject* selected; // For Alter Scene
    DisplayObject* copied;
    DisplayObjectContainer* tileMenu;

};

#endif
