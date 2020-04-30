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
Event::Event(string type, EventDispatcher* source, Player* player, string scenePath) {
    this->eventType = type;
	this->source = source;
	this->player = player;
	this->scenePath = scenePath;
    // this->switchScene = switchScene;
}
Event::Event(string type, EventDispatcher* source, Player* player, DisplayObject* enemy){
    this->eventType = type;
	this->source = source;
	this->player = player;
	this->enemy = enemy;
	// this->scenePath = scenePath;
    // this->switchScene = switchScene;
}
string Event::getType() {
    return this->eventType;
}
void Event::setType(string newtype){
    this->eventType = newtype;
}
EventDispatcher* Event::getSource() {
    return this->source;
}
Player* Event::getPlayer(){
    return this->player;
}
string Event::getScenePath(){
    return this->scenePath;
}
DisplayObject* Event::getEnemy(){
    //cout<<"in event"<<endl;
    //cout<<this->enemy<<endl;
    return this->enemy;
}

// void* Event::getData(string key) {
//     return this->data->at(key);
// }
