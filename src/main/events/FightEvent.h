#ifndef FIGHTEVENT_H
#define FIGHTEVENT_H

#include "Event.h"
#include "EventDispatcher.h"
#include "DisplayObjectContainer.h"
#include "Scene.h"

using namespace std;

class FightEvent {

public:
	FightEvent(string type, EventDispatcher* source, DisplayObjectContainer* character, DisplayObjectContainer* enemy, string scenePath);

	DisplayObjectContainer* chara;
	DisplayObjectContainer* enemy;
	string newScene;
	
private:
	string eventType = "";
	EventDispatcher* source;
};

#endif