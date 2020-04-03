#include "SceneManager.h"
#include "Layer.h"
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
        // Event* event = dynamic_cast<Event*>(event);
        // Scene* nextScene = new Scene();
        // nextScene->loadTileMap(e->getScenePath(), true);
        // Change these later according to design team
        character->position.x = 300;
        character->position.y = 500;

        Layer* layer = new Layer(); 
        layer->scrollSpeed = 1;
        layer->addChild(character);
        e->getNextScene()->addChild(layer);
        e->getNextScene()->setCharacter(character);
        SDL_Point pos = {character->position.x, character->position.y};
        prevPos = pos;
        prevS = currentS;
        EventDispatcher* ed = e->getSource();
        ed->removeEventListener(this, CHANGE);
        currentS = e->getNextScene();

        // ed->addEventListener(this, CHANGE);


    }
    else if (e->getType() == FIGHT)
    {
        // FightEvent* event = dynamic_cast<FightEvent*>(event);
        // Scene* nextScene = new Scene();
        // nextScene->loadTileMap(e->getScenePath(), true);
        // Change these later according to design team
        character->position.x = 200;
        character->position.y = 400;
        e->getEnemy()->position.x = 400;
        e->getEnemy()->position.y = 400;
        
        Layer* layer = new Layer(); 
        layer->scrollSpeed = 1;
        layer->addChild(character);
        e->getNextScene()->addChild(layer);
        e->getNextScene()->addChild(e->getEnemy());
        e->getNextScene()->setCharacter(character);
        e->getNextScene()->enemies.push_back(e->getEnemy());
        SDL_Point pos = {character->position.x, character->position.y};
        prevPos = pos;

        EventDispatcher* ed = e->getSource();
        ed->removeEventListener(this, CHANGE);
        
        prevS = currentS;
        currentS = e->getNextScene();
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