#include "Event.h"

using namespace std;

// types
// const string DO_ADDED_EVENT = "Display Object Added Event";

// Event::Event(string type, unordered_map<string, void*>* data) {
//     this->eventType = type;
//     // this->source = source;
//     this->data = data;
// }

Event::Event(string type, EventDispatcher* source) {
    this->eventType = type;
    this->source = source;
}
Event::Event(string type, Tween* tween) {
    this->eventType = type;
    this->tween = tween;
}
Event::Event(string type, EventDispatcher* source, AnimatedSprite* character, string scenePath) {
    this->eventType = type;
	this->source = source;
	this->chara = character;
	this->scenePath = scenePath;
    // this->switchScene = switchScene;
}
Event::Event(string type, EventDispatcher* source, AnimatedSprite* character, DisplayObjectContainer* enemy, string scenePath){
    this->eventType = type;
	this->source = source;
	this->chara = character;
	this->enemy = enemy;
	this->scenePath = scenePath;
    // this->switchScene = switchScene;
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
string Event::getScenePath(){
    return this->scenePath;
}
DisplayObjectContainer* Event::getEnemy(){
    return this->enemy;
}

// void* Event::getData(string key) {
//     return this->data->at(key);
// }
