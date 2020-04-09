#ifndef CONTROLLEMANAGER_H
#define CONTROLLERMANAGER_H

#include "EventListener.h"
#include "Event.h"
#include <SDL2/SDL.h>

using namespace std;


class ControllerManager : public EventListener{

public:

	ControllerManager();
	~ControllerManager();

	//This manager watches the PollEvent loop for changes in the status of the one controller.
	void handleEvent(Event* e);

    // rumbles the connected controller with intensity as a float fraction between 0 and 1
    // and a duration as milliseconds
	void rumbleController(float intensity, int duration);

private:
    SDL_GameController* controller;
	SDL_Joystick* joystick;
    SDL_Haptic* haptic;
};

#endif