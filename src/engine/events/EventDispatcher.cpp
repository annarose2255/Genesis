#include "EventDispatcher.h"

using namespace std;

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
    (*listeners)[eventType]->push_back(l);
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
