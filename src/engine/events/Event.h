#ifndef EVENT_H
#define EVENT_H

#include <string>

#include "EventDispatcher.h"

#define DO_ADDED_EVENT "Display Object Added Event"

using namespace std;

class EventDispatcher;

class Event{


public:
	
	// types
	// static const string DO_ADDED_EVENT;

	Event(string type, unordered_map<string, void*>* data = NULL);

	string getType();
	// EventDispatcher* getSource();
	void* getData(string);

private:
	string eventType = "";
	// EventDispatcher* source;
	unordered_map<string, void*>* data;
	
};

#endif