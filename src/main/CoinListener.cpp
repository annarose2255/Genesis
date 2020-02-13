#include "CoinListener.h"
#include <iostream>

CoinListener::CoinListener(DisplayObject *mc, DisplayObject *obj)
{
    object = obj;
    character = mc;
}
CoinListener::~CoinListener()
{
    delete object;
}
void CoinListener::handleEvent(Event* e)
{
    // cout << "called" << endl;
    if (e->getType().compare(PICKUP)!=0) //not sure if we need this; pretty sure dispatcher already checks
    {
        cout << "wrong event" << endl;
        return;
    }
    if (!((character->position.x > object->position.x + object->width || character->position.x + character->width < object->position.x) || (character->position.y > object->position.y + object->height || character->position.y + object->height < object->position.y)) && object->visible == true)
    {
        object->visible = false;
    }
}