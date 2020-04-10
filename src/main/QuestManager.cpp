#include "QuestManager.h"
#include <iostream>

QuestManager::QuestManager(DisplayObject *obj)
{
    object = obj;
}
QuestManager::~QuestManager()
{
    delete object;
}
void QuestManager::handleEvent(Event* e)
{
    object->visible = true;

}