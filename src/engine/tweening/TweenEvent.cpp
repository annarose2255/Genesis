#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "TweenEvent.h"
#include "Event.h"
#include "Tween.h"
#include "EventDispatcher.h"


TweenEvent::TweenEvent(string eventType, Tween* tween) : Event(eventType, tween) {
    this->eventType = eventType; 
    this->tween = tween; 
}
Tween* TweenEvent::getTween(){
    return this->tween;
}
void TweenEvent::handleEvent(Event* e)
{
   
}