#include "SceneManager.h"
#include "Layer.h"
#include "Game.h"
#include "MyGame.h"
#include "SelectionMenu.h"
#include "MenuItem.h"
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
        //load enemies + objects
        character = e->getCharacter();

        Layer* layer = new Layer(); 
        layer->scrollSpeed = 1;
        layer->addChild(character);
        nextScene->addChild(layer);
        SDL_Point pos;
        int fromRm = currentS->getSceneNum(); 
        int toRm = nextScene->getSceneNum(); //room numbers of current level and next level
        //determine where to spawn character
        if (fromRm > toRm) { 
            pos = nextScene->charEnd[fromRm]; 
            Game::camera->position.x = nextScene->right;
            Game::camera->position.y = nextScene->bottom;
        }
        else if (fromRm < toRm) {
            pos = nextScene->charStart[fromRm];
            Game::camera->position.x = nextScene->left;
            Game::camera->position.y = nextScene->bottom;
        }
        character->position.x = pos.x; 
        character->position.y = pos.y;
        
        nextScene->setCharacter(character);
        //set other enemies 
        //Save prev position & prev scene
        prevPos = pos;
        prevS = currentS;
        // EventDispatcher* ed = e->getSource();
        // ed->removeEventListener(this, CHANGE);
        currentS = nextScene;
        //remove previous scene & re-add new scene 
        Game::camera->removeImmediateChild(MyGame::currentScene);
		MyGame::currentScene = currentS;       
		Game::camera->addChild(MyGame::currentScene);
        MyGame::collisionSystem->watchForCollisions("character", "platform"); 
	    MyGame::collisionSystem->watchForCollisions("character", "enemy");
        //Tween scene in
        Tween* newFade = new Tween(currentS);
        TweenableParams alpha; 
        alpha.name = "alpha";
        newFade->animate(alpha, 0, 255, 3);
        MyGame::tj->add(newFade); 

        // ed->addEventListener(this, CHANGE);


    }
    else if (e->getType() == FIGHT)
    {
         // FightEvent* event = dynamic_cast<FightEvent*>(event);
        MyGame::collisionSystem->clearAllData();
        Scene* nextScene = new Scene();
        nextScene->inBattle = true;
        //don't load in character, save it from the previous scene
        //set it back in revert 
        //get Player instead of character??
        character = e->getCharacter();
        // Change these later according to design team
        character->position.x = 200;
        character->position.y = 400;
        e->getEnemy()->position.x = 400;
        e->getEnemy()->position.y = 400;
        
        Layer* layer = new Layer(); 
        layer->scrollSpeed = 1;
        // layer->addChild(character);
        layer->addChild(e->getEnemy());
        //add an action menu
        SelectionMenu* actionMenu = new SelectionMenu();
        // actionMenu->position.x = 0; 
        actionMenu->position.y = 600;
        MenuItem* attack = new MenuItem("Attack", 0, 0);
        MenuItem* flee = new MenuItem("Flee", 250, 0);
        // actionMenu->position.y = 600;
        //check player's state here to determine what abilities are available 
        // SelectionMenu* abilities = new SelectionMenu(); 
        //if statements with each ability!!
        // MenuItem* ghost = new MenuItem("Ghost", 0, 600);
        actionMenu->addItem(attack);
        actionMenu->addItem(flee);
        // attack->nextMenu = abilities; 
        // abilities->addItem(ghost);
        // nextScene->addChild(abilities);
        nextScene->addChild(actionMenu);
        actionMenu->visible = true;
        nextScene->addChild(layer);

        nextScene->setCharacter(character);
        nextScene->setEnemy(e->getEnemy());

        SDL_Point pos = {character->position.x, character->position.y};
        prevPos = pos;

        EventDispatcher* ed = e->getSource();
        // ed->removeEventListener(this, CHANGE);

        prevS = currentS;
        currentS = nextScene;
        Game::camera->removeImmediateChild(MyGame::currentScene);
        //Transition to scene
		MyGame::currentScene = currentS;       
		Game::camera->addChild(MyGame::currentScene);
        Tween* newFade = new Tween(currentS);
        TweenableParams alpha; 
        alpha.name = "alpha"; 
        newFade->animate(alpha, 0, 255, 3);
        MyGame::tj->add(newFade); 
    }
    else if (e->getType() == REVERT) 
    {
        currentS = prevS;
        //
        //currentS->isBattle = false;
        character->position = prevPos;
    }
}

Scene* SceneManager::getCurrentScene(){
    return this->currentS;
}