#ifndef TWEENEVENT_H
#define TWEENEVENT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <SDL2/SDL_ttf.h>
#include "Event.h"
#include "EventDispatcher.h"
#include "Tween.h"

class TweenEvent: public Event{ 
    
public:
	//list of static final strings, e.g. tween_complete_event
    TweenEvent(string eventType, Tween* tween);
    Tween* getTween();
    void handleEvent(Event* e);

private:
    Tween* tween; 
    string eventType;

	
};

#endif