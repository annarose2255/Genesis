#include "SceneManager.h"
#include <iostream>

SceneManager::SceneManager(DisplayObject *chara, Scene *s)
{
    currentS = s;
    character = chara;
}
SceneManager::~SceneManager()
{
    delete door;
}
void SceneManager::handleEvent(Event* e)
{
    if (e->getType() == CHANGE)
    {
        ChangeSceneEvent* event = dynamic_cast<ChangeSceneEvent*>(event);
        Scene* nextScene = new Scene();
        nextScene->loadScene(event->newScene);
        nextScene->addChild(character);

        // Change these later according to design team
        character->position.x = 200;
        character->position.y = 200;
        EventDispatcher* ed = event->getSource();
        ed->removeEventListener(this, CHANGE);
        currentS = nextScene;


    }
    else if (e->getType() == FIGHT)
    {
        FightEvent* event = dynamic_cast<FightEvent*>(event);
        Scene* nextScene = new Scene();
        nextScene->loadScene(event->newScene);
        nextScene->addChild(character);
        nextScene->addChild(event->enemy);
        SDL_Point pos = {character->position.x, character->position.y};
        prevPos = pos;

        // Change these later according to design team
        character->position.x = 200;
        character->position.y = 200;
        event->enemy->position.x = 400;
        event->enemy->position.y = 400;

        EventDispatcher* ed = event->getSource();
        ed->removeEventListener(this, CHANGE);
        
        prevS = currentS;
        currentS = nextScene;

        ed->addEventListener(this, REVERT);
    }
    else if (e->getType() == REVERT) 
    {
        currentS = prevS;
        character->position = prevPos;
    }
}
