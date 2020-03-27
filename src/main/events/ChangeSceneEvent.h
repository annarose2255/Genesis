#ifndef CHANGESCENEEVENT_H
#define CHANGESCENEEVENT_H

#include "Event.h"
#include "DisplayObjectContainer.h"
#include "Scene.h"

using namespace std;

class ChangeSceneEvent : Event {

public:
	ChangeSceneEvent(string type, EventDispatcher* source, DisplayObjectContainer* character, string scenePath);

	DisplayObjectContainer* chara;
	string newScene;

private:

};

#endif