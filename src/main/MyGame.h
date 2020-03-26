#ifndef MYGAME_H
#define MYGAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Game.h"
#include "Sprite.h"
<<<<<<< HEAD
#include "Sound.h"
#include "AnimatedSprite.h"
#include "Scene.h"
#include "Camera.h"
#include "CoinListener.h"
=======
#include "AnimatedSprite.h"
#include "Scene.h"
>>>>>>> 28124d242415859506e8cf02a75402fa03d3229c

using namespace std;

class MyGame : public Game{

public:
	MyGame();
	virtual ~MyGame();

	virtual void update(set<SDL_Scancode> pressedKeys);
<<<<<<< HEAD
	virtual void draw(AffineTransform &, SDL_Rect camera);
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
    Camera* cam;

    EventListener* coinlis;
	EventListener* myQuestManager;
	EventDispatcher* eDispatcher;
    DisplayObjectContainer *questComplete;
    bool isOngoing = true;

    bool isCharInCoin(DisplayObject* chara, DisplayObject* cn);
=======
	virtual void draw(AffineTransform &at);

private:
    
    bool change;
    Scene* currentScene;    
    Scene* scene1;
    Scene* scene2;    	
>>>>>>> 28124d242415859506e8cf02a75402fa03d3229c

};

#endif
