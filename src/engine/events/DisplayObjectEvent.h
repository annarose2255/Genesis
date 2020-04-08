#ifndef DISPLAYOBJECTEVENT_H
#define DISPLAYOBJECTEVENT_H

#include "Event.h"
#include "DisplayObject.h"

using namespace std;

class DisplayObjectEvent : public Event {

public:
	DisplayObjectEvent(string type, EventDispatcher* source, DisplayObject* displayObject);

	DisplayObject* displayObject;
	
// private:
// 	string eventType = "";
// 	EventDispatcher* source;
};

#endif