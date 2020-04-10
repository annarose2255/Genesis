#ifndef DEVTOOL_H
#define DEVTOOL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Game.h"
#include "Sprite.h"
#include "AnimatedSprite.h"
#include "Scene.h"
#include "Camera.h"
#define SPRITESIZE 100
using namespace std;

class DevTool : public Game{

public:
	DevTool();
	virtual ~DevTool();

	virtual void update(set<SDL_Scancode> pressedKeys, ControllerInput controllerInput);
	virtual void draw(AffineTransform &at);
    virtual void start();

    void IterateDirectory(string filepath);
    void load(string filepath);
    void save(string filepath);
    DisplayObjectContainer * sceneClick(int x, int y);
    bool inSquare(DisplayObjectContainer *parent, int x, int y);
    DisplayObjectContainer *sceneClickHelper(DisplayObjectContainer *sceneObj, int x, int y);
    void tileSnap(DisplayObjectContainer *obj);
    void copy();
    void paste(); 
    void drawGrid();

private:
    
    // Camera* cam;
    Scene* currentScene;
    DisplayObjectContainer* selected; // For Alter Scene
    DisplayObjectContainer* copied = NULL;
    Scene* sceneWindow;
    DisplayObjectContainer* tileMenu;
    SDL_Point initMouseLoc = {-1, -1};
    SDL_Point currMouseLoc = {-1, -1};
    int num = 0;

};

#endif
