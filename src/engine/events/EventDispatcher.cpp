#include "EventDispatcher.h"

using namespace std;

EventDispatcher* EventDispatcher::instance;

EventDispatcher* EventDispatcher::getInstance() {
    if (!instance){
        instance = new EventDispatcher();
    }
    return instance;
}

EventDispatcher::EventDispatcher() {
    listeners = new unordered_map<string, vector<EventListener*>*>();
}

EventDispatcher::~EventDispatcher() {
    for(pair<string, vector<EventListener*>*> listener : (*listeners)) {
        vector<EventListener*> * eList = listener.second;
        for(EventListener* l : (*eList)) {
            delete l;
        }
        delete eList;
    }
    delete listeners;
}

void EventDispatcher::addEventListener(EventListener* l, string eventType) {
    if ( listeners->find(eventType) != (*listeners).end() ){
        (*listeners)[eventType]->push_back(l);
    } else {
        vector<EventListener*>* el = new vector<EventListener*>();
        el->push_back(l);
        listeners->insert(pair<string, vector<EventListener*>*>(eventType, el));
    }
}

void EventDispatcher::removeEventListener(EventListener* l, string eventType) {
    for(int i=0; i<(*listeners)[eventType]->size(); i++) {
        if(l == (*(*listeners)[eventType])[i]) {
            (*listeners)[eventType]->erase((*listeners)[eventType]->begin()+i);
        }
    }
}

bool EventDispatcher::hasEventListener(EventListener* l, string eventType) {
    vector<EventListener*> *temp = (*listeners)[eventType];
    for(int i=0; i<temp->size(); i++) {
        if((*temp)[i] == l) return true;
    }
    return false;
}

void EventDispatcher::dispatchEvent(Event *e) {
    for(pair<string, vector<EventListener*>*> listener : *listeners) {
        string eType = listener.first;
        vector<EventListener*> *l = listener.second;
        for(int i=0; i<l->size(); i++) {
            (*l)[i]->handleEvent(e);
        }
    }
}
