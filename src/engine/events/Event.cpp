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

string Event::getType() {
    return this->eventType;
}

EventDispatcher* Event::getSource() {
    return this->source;
}

// void* Event::getData(string key) {
//     return this->data->at(key);
// }
