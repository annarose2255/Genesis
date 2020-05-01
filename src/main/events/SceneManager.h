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
#define DEFEATEDENEMY "EnemyIsDefeated"
#define DECIDEFATE "DecideEnemyFate"
#define SPARE "SpareEnemy"
#define KILL "KillEnemy"
#define CONSUME "ConsumeEnemy"
#define DEFEND "PlayerDefendAction"
#define TRANSFORM "PlayerTransformAction"
#define GHOST "PlayerGhostTransform"
#define STRENGTHCOMBAT "PlayerStrengthTransform"
#define DEATH "PlayerDeath"

class SceneManager: public EventListener{

public:
    static SceneManager* getInstance();
    SceneManager(Player* chara, Scene* s);
    SceneManager();
    ~SceneManager();
	void handleEvent(Event* e);
    Scene* getCurrentScene();
    HealthBar* playerHP;
    HealthBar* enemyHP; 
    Scene* startS;
    SDL_Point startPos;
    SDL_Point startCam;

private:
    static SceneManager* instance;
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
    bool enemyDefeated = false;
    int blockUse = 0;
    bool ghostAbility = false;
    int lasting = 0;
    int cooldown = 4;
    int enemyDamage = 5;
    int baseEnemyDamage = 5;
    int playerdamage = 10;
    int turnCount = 0; //the current turn #
    int turnAbilityUse = 0; // turn where ability can be used again
    int turnAbilityStop = 0; //turn where ability stops being used;
    string lastAction = "";
    string playerLastAction ="";
};

#endif