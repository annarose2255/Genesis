#ifndef EVENT_H
#define EVENT_H

#include <string>

#include "EventDispatcher.h"

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

	string getType();
	EventDispatcher* getSource();

private:
	string eventType = "";
	EventDispatcher* source;
	
};

#endif