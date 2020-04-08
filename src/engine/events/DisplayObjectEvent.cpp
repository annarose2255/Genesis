#include "DisplayObjectEvent.h"
#include "Event.h"
using namespace std;

DisplayObjectEvent::DisplayObjectEvent(string type, EventDispatcher* source, DisplayObject* displayObject) : Event(type, source) {
	this->displayObject = displayObject;
}