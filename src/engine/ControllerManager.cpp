#include "EventListener.h"
#include "Event.h"
#include "ControllerManager.h"
#include "ControllerEvent.h"
#include <SDL2/SDL.h>
#include <iostream>

using namespace std;


ControllerManager::ControllerManager(){
    controller = NULL;
    joystick = NULL;
    haptic = NULL;
}

ControllerManager::~ControllerManager(){

}

//This manager watches the PollEvent loop for changes in the status of the one controller.
void ControllerManager::handleEvent(Event* e){
    if (e->getType() == CONTROLLER_ADDED_EVENT){
        ControllerEvent* cEvent = (ControllerEvent*) e;
        this->controller = cEvent->controller;
        cout << "Controller connected." << endl;
        this->rumbleController(0.3, 500);
    }
    if (e->getType() == CONTROLLER_REMOVED_EVENT){
        ControllerEvent* cEvent = (ControllerEvent*) e;
        SDL_GameControllerClose(this->controller);
        this->controller = NULL;
        this->joystick = NULL;
        if (this->haptic){
            SDL_HapticClose(this->haptic);
            this->haptic = NULL;
        }
        cout << "Controller disconnected." << endl;
    }
}

// rumbles the connected controller with intensity as a float fraction between 0 and 1
// and a duration as milliseconds
void ControllerManager::rumbleController(float intensity, int duration){
    if (controller){
        //Get controller haptic device 
        if (joystick == NULL){
            joystick = SDL_GameControllerGetJoystick(controller);
        }
        if (haptic == NULL){
            haptic = SDL_HapticOpenFromJoystick(joystick);
        }
        if (SDL_HapticRumbleInit(haptic) != 0)
        {
            SDL_HapticClose(haptic);
            haptic = 0;
        }
        SDL_HapticRumblePlay(haptic, intensity, duration);
    } else {
        cout << "Sorry, controller is not connected." << endl;
    }
}