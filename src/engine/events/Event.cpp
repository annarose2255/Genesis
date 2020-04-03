#include "Event.h"

using namespace std;

Event::Event(string type, EventDispatcher* source) {
    this->eventType = type;
    this->source = source;
}
Event::Event(string type, EventDispatcher* source, AnimatedSprite* character, Scene* switchScene) {
    this->eventType = type;
	this->source = source;
	this->chara = character;
	// this->scenePath = scenePath;
    this->switchScene = switchScene;
}
Event::Event(string type, EventDispatcher* source, AnimatedSprite* character, DisplayObjectContainer* enemy, Scene* switchScene){
    this->eventType = type;
	this->source = source;
	this->chara = character;
	this->enemy = enemy;
	// this->scenePath = scenePath;
    this->switchScene = switchScene;
}
string Event::getType() {
    return this->eventType;
}

EventDispatcher* Event::getSource() {
    return this->source;
}
AnimatedSprite* Event::getCharacter(){
    return this->chara;
}
Scene* Event::getNextScene(){
    return this->switchScene;
}
DisplayObjectContainer* Event::getEnemy(){
    return this->enemy;
}
