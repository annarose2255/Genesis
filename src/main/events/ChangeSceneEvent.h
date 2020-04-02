#ifndef CHANGESCENEEVENT_H
#define CHANGESCENEEVENT_H

#include "DisplayObjectContainer.h"
#include "EventDispatcher.h"
#include "Scene.h"

using namespace std;

class ChangeSceneEvent{

public:
	ChangeSceneEvent(string type, EventDispatcher* source, DisplayObjectContainer* character, string scenePath);

	DisplayObjectContainer* chara;
	string newScene;

private:
	string eventType = "";
	EventDispatcher* source;
};

#endif