#ifndef CONTROLLEREVENT_H
#define CONTROLLEREVENT_H

#include "Event.h"
#include <SDL2/SDL.h>

using namespace std;

class ControllerEvent : public Event {

public:
	ControllerEvent(string type, EventDispatcher* source, SDL_GameController* controller);

	SDL_GameController* controller;
	
};

#endif