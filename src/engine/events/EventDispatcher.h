#ifndef EVENTDISPATCHER_H
#define EVENTDISPATCHER_H

#include <unordered_map>
#include <vector>
#include <string>

#include "Event.h"
#include "EventListener.h"


using namespace std;

class EventListener;
class Event;

class EventDispatcher{

public:
	// EventDispatcher();
	static EventDispatcher* getInstance();
	virtual ~EventDispatcher();
	
	void addEventListener(EventListener* l, string eventType);
	void removeEventListener(EventListener* l, string eventType);
	bool hasEventListener(EventListener* l, string eventType);
	void dispatchEvent(Event *e);

private:
	static EventDispatcher* instance;
	EventDispatcher();
	/* List of listeners */
	std::unordered_map<std::string, std::vector<EventListener*>*> *listeners;


};

#endif