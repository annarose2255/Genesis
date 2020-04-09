#include "ControllerEvent.h"
#include "Event.h"

using namespace std;

ControllerEvent::ControllerEvent(string type, EventDispatcher* source, SDL_GameController* controller) : Event(type, source) {
	this->controller = controller;
}