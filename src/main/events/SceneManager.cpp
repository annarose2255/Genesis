#include "SceneManager.h"
#include "Layer.h"
#include "Game.h"
#include "MyGame.h"
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
        MyGame::collisionSystem->clearAllData();
        Scene* nextScene = new Scene();
        nextScene->loadTileMap(e->getScenePath());
        character = e->getCharacter();
        //Change to start or end of level...store this info as part of class?
        //event should hold info as to whether or not this is changing to the start/end 
            //of a level 
        // character->position.x = 300;
        // character->position.y = 500;

        Layer* layer = new Layer(); 
        layer->scrollSpeed = 1;
        layer->addChild(character);
        nextScene->addChild(layer);
        SDL_Point pos;
        int fromRm = currentS->getSceneNum(); 
        int toRm = nextScene->getSceneNum(); //room numbers of current level and next level
        //determine where to spawn character
        if (fromRm > toRm) { 
            pos = nextScene->charEnd[currentS->getSceneNum()]; 
            Game::camera->position.x = nextScene->right;
            Game::camera->position.y = nextScene->bottom;
        }
        else if (fromRm < toRm) {
            pos = nextScene->charStart[currentS->getSceneNum()];
            Game::camera->position.x = nextScene->left;
            Game::camera->position.y = nextScene->bottom;
        }
        cout << "Char pos x " << pos.x << endl;
        cout << "Char pos y " << pos.y << endl;
        character->position.x = pos.x; 
        character->position.y = pos.y;
        
        nextScene->setCharacter(character);
        //set other enemies 
        // SDL_Point pos = {character->position.x, character->position.y};
        prevPos = pos;
        prevS = currentS;
        EventDispatcher* ed = e->getSource();
        // ed->removeEventListener(this, CHANGE);
        currentS = nextScene;
        //remove previous scene 
        Game::camera->removeImmediateChild(MyGame::currentScene);
        //Scene Transitions
		MyGame::currentScene = currentS;       
		Game::camera->addChild(MyGame::currentScene);
        //if prevS > currentS 
        //Game::camera->position.x = prevS->right; 
        //Game::camera->position.y = prevS->bottom;
        MyGame::collisionSystem->watchForCollisions("character", "platform"); 
	    MyGame::collisionSystem->watchForCollisions("character", "enemy");
        // Tween* prevFade = new Tween(prevS);
        Tween* newFade = new Tween(currentS);
        // Tween* charIn = new Tween(currentS->getCharacter());
        TweenableParams alpha; 
        alpha.name = "alpha";
        // prevFade->animate(alpha, 255, 0, 2); 
        newFade->animate(alpha, 0, 255, 3);

        // MyGame::tj->add(prevFade); 
        MyGame::tj->add(newFade); 

        // ed->addEventListener(this, CHANGE);


    }
    else if (e->getType() == FIGHT)
    {
         // FightEvent* event = dynamic_cast<FightEvent*>(event);
        Scene* nextScene = new Scene();
        nextScene->loadTileMap(e->getScenePath());
        character = e->getCharacter();
        // Change these later according to design team
        character->position.x = 200;
        character->position.y = 400;
        e->getEnemy()->position.x = 400;
        e->getEnemy()->position.y = 400;
        
        Layer* layer = new Layer(); 
        layer->scrollSpeed = 1;
        layer->addChild(character);
        nextScene->addChild(layer);
        nextScene->addChild(e->getEnemy());
        nextScene->setCharacter(character);
        nextScene->addEnemy(e->getEnemy());
        // nextScene->enemies.push_back(e->getEnemy());
        SDL_Point pos = {character->position.x, character->position.y};
        prevPos = pos;

        EventDispatcher* ed = e->getSource();
        // ed->removeEventListener(this, CHANGE);
    
        prevS = currentS;
        currentS = nextScene;
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