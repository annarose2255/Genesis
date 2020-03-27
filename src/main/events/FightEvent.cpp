#include "ChangeSceneEvent.h"

using namespace std;

ChangeSceneEvent::ChangeSceneEvent(string type, EventDispatcher* source, DisplayObjectContainer* character, string scenePath) {
	this->eventType = type;
	this->source = source;
	this->chara = character;
	this->enemy = enemy;
	this->newScene = scenePath;
}