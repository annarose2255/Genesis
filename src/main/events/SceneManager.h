#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "Event.h"
#include "EventListener.h"
#include "AnimatedSprite.h"
#include "Scene.h"
#include "FightEvent.h"
#include "ChangeSceneEvent.h"
#define CHANGE "RoomChangeEvent"
#define FIGHT "EngageCombatEvent" 
#define REVERT "RevertEvent"

class SceneManager: public EventListener{

public:

    SceneManager(AnimatedSprite* chara, Scene* s);
    ~SceneManager();
	void handleEvent(Event* e);
    Scene* getCurrentScene();

private:	
    Scene* currentS;
	Scene* prevS;
	SDL_Point prevPos;
    DisplayObject* door;
    AnimatedSprite* character;
};

#endif