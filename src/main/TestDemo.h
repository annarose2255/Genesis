#ifndef TESTDEMO_H
#define TESTDEMO_H

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
#include "EventDispatcher.h"
#include "SceneManager.h"
#include "TweenJuggler.h"
#include "HealthBar.h"
#include "TextBox.h"
#include "SelectionMenu.h"

using namespace std;

class TestDemo : public Game{

public:
	TestDemo();
	virtual ~TestDemo();

	virtual void update(set<SDL_Scancode> pressedKeys, set<SDL_GameControllerButton> pressedButtons, set<pair<SDL_GameControllerAxis, float>> movedAxis);
	virtual void draw(AffineTransform &at);
    Scene* currentScene;

    int viewportWidth = 800;
	int viewportHeight = 700;
    
    const int levelWidth = 1280;
	const int levelHeight = 960;

    // UI Components
    HealthBar* hp;
    TextBox* tBox;
    SelectionMenu* mainMenu;

private:
    Sound* mainMusic;
    
    bool change;    
    Scene* scene1;
    Scene* scene2; 
    Scene* scene3;   	
    // Camera* cam;
    TweenJuggler* tj;
    EventDispatcher* eDispatcher;
    EventListener* coinlis;
	EventListener* myQuestManager;
    DisplayObjectContainer *questComplete;
    SceneManager* sm;
    bool isOngoing = true;
    bool fight = false;
    bool isCharInCoin(DisplayObject* chara, DisplayObject* cn);


};

#endif
