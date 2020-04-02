#ifndef EVENT_H
#define EVENT_H

#include <string>

#include "EventDispatcher.h"
#include "AnimatedSprite.h"
#include "Scene.h"
#include "DisplayObjectContainer.h"

using namespace std;

class EventDispatcher;

class Event{

public:

	Event(string type, EventDispatcher* source);
	Event(string type, EventDispatcher* source, AnimatedSprite* character, Scene* switchScene); //change scene
	Event(string type, EventDispatcher* source, AnimatedSprite* character, DisplayObjectContainer* enemy, Scene* switchScene);
	string getType();
	EventDispatcher* getSource();
	AnimatedSprite* getCharacter(); 
	Scene* getNextScene(); 
	DisplayObjectContainer* getEnemy(); 
private:
	string eventType = "";
	EventDispatcher* source;
	AnimatedSprite* chara;
	DisplayObjectContainer* enemy;
	string scenePath;
	Scene* switchScene;
	
};

#endif