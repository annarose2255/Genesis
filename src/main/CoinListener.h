#ifndef COINLISTENER_H
#define COINLISTENER_H

#include "Event.h"
#include "EventListener.h"
#include "AnimatedSprite.h"
#define PICKUP "PICKUP" 

class CoinListener: public EventListener{

public:

    CoinListener(DisplayObject *mc, DisplayObject *obj);
    ~CoinListener();
	void handleEvent(Event* e) = 0;

private:	
    DisplayObject* character;
    DisplayObject* object;
};

#endif