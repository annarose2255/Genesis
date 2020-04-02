#include "SceneManager.h"
#include <iostream>

SceneManager::SceneManager(AnimatedSprite* chara, Scene* s)
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
        cout << "inside change!" << endl;
        // Event* event = dynamic_cast<Event*>(event);
        Scene* nextScene = new Scene();
        cout << "new scene path " << endl;
        // nextScene->loadTileMap(e->getScenePath(), true);
        cout << "loaded map " << endl;
        nextScene->addChild(character);

        // Change these later according to design team
        character->position.x = 70;
        character->position.y = 370;
        EventDispatcher* ed = e->getSource();
        ed->removeEventListener(this, CHANGE);
        currentS = nextScene;

        ed->addEventListener(this, CHANGE);


    }
    else if (e->getType() == FIGHT)
    {
        // FightEvent* event = dynamic_cast<FightEvent*>(event);
        Scene* nextScene = new Scene();
        // nextScene->loadTileMap(e->getScenePath(), true);
        nextScene->addChild(character);
        nextScene->addChild(e->getEnemy());
        SDL_Point pos = {character->position.x, character->position.y};
        prevPos = pos;

        // Change these later according to design team
        character->position.x = 200;
        character->position.y = 200;
        e->getEnemy()->position.x = 400;
        e->getEnemy()->position.y = 400;

        EventDispatcher* ed = e->getSource();
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

Scene* SceneManager::getCurrentScene(){
    return this->currentS;
}