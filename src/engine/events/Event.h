#ifndef EVENT_H
#define EVENT_H

#include <string>

#include "EventDispatcher.h"
#include "AnimatedSprite.h"
#include "Tween.h"
#include "DisplayObjectContainer.h"

#define DO_ADDED_EVENT "Display Object Added Event"
#define CONTROLLER_ADDED_EVENT "Controller Added Event"
#define CONTROLLER_REMOVED_EVENT "Controller Removed Event"

using namespace std;

class EventDispatcher;

class Event{


public:
	
	// types
	// static const string DO_ADDED_EVENT;

	Event(string type, EventDispatcher* source);
	Event(string type, Tween* tween);
	Event(string type, EventDispatcher* source, AnimatedSprite* character, string scenePath); //change scene
	Event(string type, EventDispatcher* source, AnimatedSprite* character, DisplayObject* enemy);
	string getType();
	EventDispatcher* getSource();
	AnimatedSprite* getCharacter(); 
	string getScenePath(); 
	DisplayObject* getEnemy(); 
private:
	string eventType = "";
	EventDispatcher* source;
	AnimatedSprite* chara;
	DisplayObject* enemy;
	string scenePath;
	Tween* tween;
	// Scene* switchScene;
	
};

#endif