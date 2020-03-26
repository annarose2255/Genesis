#ifndef QUESTMANAGER_H
#define QUESTMANAGER_H

#include "Event.h"
#include "EventListener.h"
#include "AnimatedSprite.h"
#include "CoinListener.h" 

class QuestManager: public EventListener{

public:

    QuestManager(DisplayObject *obj);
    ~QuestManager();
	void handleEvent(Event* e);

private:	
    // DisplayObject* character;
    DisplayObject* object;
};

#endif