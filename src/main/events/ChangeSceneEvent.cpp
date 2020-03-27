#include "ChangeSceneEvent.h"
#include "Event.h"

using namespace std;

ChangeSceneEvent::ChangeSceneEvent(string type, EventDispatcher* source, DisplayObjectContainer* character, string scenePath) : Event(type, source) {
	this->eventType = type;
	this->source = source;
	this->chara = character;
	this->newScene = scenePath;
}