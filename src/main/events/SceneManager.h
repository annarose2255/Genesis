#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "Event.h"
#include "EventListener.h"
#include "AnimatedSprite.h"
#include "Scene.h"
#define CHANGE "RoomChangeEvent"
#define FIGHT "EngageCombatEvent" 
#define REVERT "RevertEvent"

class SceneManager: public EventListener{

public:

    SceneManager(DisplayObject *chara, Scene *s);
    ~SceneManager();
	void handleEvent(Event* e);

private:	
	Scene* currentS;
	Scene* prevS;
	SDL_Point prevPos;
    DisplayObject* door;
    DisplayObject* character;
};

#endif