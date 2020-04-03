#include "FightEvent.h"
using namespace std;

FightEvent::FightEvent(string type, EventDispatcher* source, DisplayObjectContainer* character, DisplayObjectContainer* enemy, string scenePath) {
	this->eventType = type;
	this->source = source;
	this->chara = character;
	this->enemy = enemy;
	this->newScene = scenePath;
}