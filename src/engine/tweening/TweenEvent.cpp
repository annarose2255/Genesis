#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "TweenEvent.h"
#include "Event.h"
#include "Tween.h"
#include "EventDispatcher.h"


TweenEvent::TweenEvent(string eventType, EventDispatcher* source, Tween tween) : Event(eventType, source) {

}
Tween TweenEvent::getTween(){

}