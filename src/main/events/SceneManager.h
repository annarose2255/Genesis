#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "Event.h"
#include "EventListener.h"
// #include "AnimatedSprite.h"
#include "Player.h"
#include "Scene.h"
#include "HealthBar.h"
#define CHANGE "RoomChangeEvent"
#define FIGHT "EngageCombatEvent" 
#define REVERT "RevertEvent"
#define REVERTBATTLE "RevertFromBattleEvent"
#define ATTACK "PlayerAttackEvent"
#define ENEMYTURN "EnemyEvent"

class SceneManager: public EventListener{

public:

    SceneManager(Player* chara, Scene* s);
    ~SceneManager();
	void handleEvent(Event* e);
    Scene* getCurrentScene();
    HealthBar* playerHP;
    HealthBar* enemyHP; 

private:	
    Scene* currentS;
	Scene* prevS;
	SDL_Point prevPos;
    SDL_Point prevCam;
    DisplayObject* door;
    // AnimatedSprite* character;
    Player* player;
    DisplayObject* chara; 
    bool jumpAbility = false;
    bool block = false;
    int abilityUse = 0;
    int blockUse = 0;
    bool ghostAbility = false;
    int cooldown = 0;
    string lastAction = "";
};

#endif