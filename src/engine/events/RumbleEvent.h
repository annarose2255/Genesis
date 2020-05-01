#ifndef RUMBLEEVENT_H
#define RUMBLEEVENT_H

#include "Event.h"
#include <SDL2/SDL.h>

using namespace std;

class RumbleEvent : public Event {

public:
    RumbleEvent(string type, EventDispatcher* source, float intensity, int duration);

	float intensity;
    int duration;
	
};

#endif