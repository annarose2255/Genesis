#ifndef COINLISTENER_H
#define COINLISTENER_H

#include "Event.h"
#include "EventListener.h"
#include "AnimatedSprite.h"
#define PICKUP "MovedEvent"
#define COLLECTED "PickedUpEvent" 

class CoinListener: public EventListener{

public:

    CoinListener(DisplayObject *mc, DisplayObject *obj);
    ~CoinListener();
	void handleEvent(Event* e);

private:	
    DisplayObject* object;
    DisplayObject* character;
};

#endif