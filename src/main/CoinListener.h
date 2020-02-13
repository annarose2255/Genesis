#ifndef COINLISTENER_H
#define COINLISTENER_H

#include "Event.h"
#include "EventListener.h"
#define PICKUP "PICKUP" 
class CoinListener:EventListener{

public:
    CoinListener(DisplayObject *mc, DisplayObject *obj);
    ~CoinListener();
	virtual void handleEvent(Event* e) = 0;

private:	
    DisplayObject* character;
    DisplayObject* object;
};

#endif