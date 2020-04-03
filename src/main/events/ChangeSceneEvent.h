#ifndef CHANGESCENEEVENT_H
#define CHANGESCENEEVENT_H

#include "DisplayObjectContainer.h"
#include "Scene.h"
#include "Event.h"

using namespace std;

class ChangeSceneEvent : public Event{

public:
	ChangeSceneEvent(string type, EventDispatcher* source, DisplayObjectContainer* character, string scenePath);

	DisplayObjectContainer* chara;
	string newScene;

private:
	string eventType = "";
	EventDispatcher* source;
};

#endif