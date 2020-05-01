#ifndef MYGAME_H
#define MYGAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "../Game.h"
//#include "Sprite.h"
#include "Sound.h"
//#include "AnimatedSprite.h" 
#include "Scene.h"
//#include "Camera.h"
//#include "CoinListener.h"
#include "EventDispatcher.h"
#include "SceneManager.h"
#include "TweenJuggler.h"
#include "CollisionSystem.h"
#include "HealthBar.h"
#include "TextBox.h"
#include "SelectionMenu.h"
#include "Controls.h"

using namespace std;

class MyGame : public Game{

public:
	MyGame();
	virtual ~MyGame();

	virtual void update(set<SDL_Scancode> pressedKeys, set<SDL_GameControllerButton> pressedButtons, set<pair<SDL_GameControllerAxis, float>> movedAxis);
	virtual void draw(AffineTransform &at);
    static Scene* currentScene;

    int viewportWidth = 800;
	int viewportHeight = 700;
    
    const int levelWidth = 1280;
	const int levelHeight = 960;

    // UI Components
    // HealthBar* hp;
    TextBox* tBox;
    SelectionMenu* mainMenu;
    SelectionMenu* itemsMenu;

    static EventDispatcher* eDispatcher;
    static TweenJuggler* tj;
    static CollisionSystem* collisionSystem; 
    static Controls* controls;
    static SelectionMenu* actionMenu; 
    static SelectionMenu* abilities; 
    static SelectionMenu* decision; 
    static SelectionMenu* enemyFate; 
    static Layer* forestBG; 
private:
    Sound* mainMusic;
    
    bool change = false; 
    bool tchange = true;    
    Scene* scene1;
    // Scene* scene2; 
    // Scene* scene3;   	
    // Camera* cam;
    // TweenJuggler* tj;
    // EventListener* coinlis;
	// EventListener* myQuestManager;
    // DisplayObjectContainer *questComplete;
    SceneManager* sm;
    bool isOngoing = true;
    bool fight = false;
    MenuItem* attack;
    MenuItem* defend;
    MenuItem* transform;
    MenuItem* flee;
    MenuItem* spare; 
    MenuItem* kill;
    MenuItem* consume; 
    HealthBar* hp; 
    HealthBar* enemyHP;
    // bool isCharInCoin(DisplayObject* chara, DisplayObject* cn);


};

#endif
