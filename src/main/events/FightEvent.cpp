#include "FightEvent.h"
#include "Event.h"
using namespace std;

FightEvent::FightEvent(string type, EventDispatcher* source, DisplayObjectContainer* character, DisplayObjectContainer* enemy, string scenePath) : Event(type, source) {
	this->eventType = type;
	this->source = source;
	this->chara = character;
	this->enemy = enemy;
	this->newScene = scenePath;
}