#include "CoinListener.h"

CoinListener::CoinListener(DisplayObject *mc, DisplayObject *obj)
{
    character = mc;
    object = obj;
}
CoinListener::~CoinListener()
{
    delete character;
    delete object;
}
void CoinListener::handleEvent(Event* e)
{
    if (e->getType().compare(PICKUP)!=0) //not sure if we need this; pretty sure dispatcher already checks
    {
        return;
    }
    if (!((character->position.x > object->position.x + object->width || character->position.x + character->width < object->position.x) || (character->position.y > object->position.y + object->height || character->position.y + object->height < object->position.y)) )
    {
        object->visible = false;
    }
}