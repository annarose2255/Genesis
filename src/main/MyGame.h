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
#include "CoinListener.h"
#include "SceneManager.h"

using namespace std;

class MyGame : public Game{

public:
	MyGame();
	virtual ~MyGame();

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);
    Scene* currentScene;

    int viewportWidth = 800;
	int viewportHeight = 700;
    
    const int levelWidth = 1280;
	const int levelHeight = 960;

private:
    Sound* mainMusic;
    
    bool change;    
    Scene* scene1;
    Scene* scene2; 
    Scene* scene3;   	
    // Camera* cam;

    EventListener* coinlis;
	EventListener* myQuestManager;
	EventDispatcher* eDispatcher;
    DisplayObjectContainer *questComplete;
    SceneManager* sm;
    bool isOngoing = true;
    bool fight = false;
    bool isCharInCoin(DisplayObject* chara, DisplayObject* cn);

};

#endif
