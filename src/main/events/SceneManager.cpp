#include "SceneManager.h"
#include "Layer.h"
#include "Game.h"
#include "MyGame.h"
#include "SelectionMenu.h"
#include "MenuItem.h"
#include <iostream>

SceneManager::SceneManager(Player* chara, Scene* s)
{
    currentS = s;
    player = chara;
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
        int fromRm = currentS->getSceneNum(); 
        int toRm = nextScene->getSceneNum(); //room numbers of current level and next level
        string otherFilepath = "./resources/scenes/Room"+ to_string(toRm) + ".json"; //get filepath for enemies in scene
        nextScene->loadScene(otherFilepath); 
        //load enemies + objects
        player = e->getPlayer();

        Layer* layer = new Layer(); 
        layer->scrollSpeed = 1;
        layer->addChild(player);
        nextScene->addChild(layer);
        SDL_Point pos;
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
        player->position.x = pos.x; 
        player->position.y = pos.y;
        
        nextScene->setPlayer(player);
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
        MyGame::collisionSystem->watchForCollisions("player", "platform"); 
	    MyGame::collisionSystem->watchForCollisions("player", "enemy");
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
        // MyGame::collisionSystem->clearAllData();
        Scene* nextScene = new Scene();
        nextScene->inBattle = true;
        //don't load in character, save it from the previous scene
        //set it back in revert 
        //get Player instead of character??
        player = e->getPlayer();
        // Change these later according to design team
        // character->position.x = 200;
        // character->position.y = 400;
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
        flee->setAction(new Event(REVERTBATTLE, MyGame::eDispatcher, player, e->getEnemy()));
        // actionMenu->position.y = 600;
        //check player's state here to determine what abilities are available 
        SelectionMenu* abilities = new SelectionMenu(); 
        abilities->position.y = 600;
        //if statements with each ability!!
        MenuItem* ghost = new MenuItem("Ghost", 0, 0);
        actionMenu->addItem(attack);
        actionMenu->addItem(flee);
        attack->nextMenu = abilities; 
        abilities->addItem(ghost);
        nextScene->addChild(actionMenu);
        nextScene->addChild(abilities);
        actionMenu->visible = true;
        nextScene->addChild(layer);

        nextScene->setPlayer(player);
        nextScene->setEnemy(e->getEnemy());

        SDL_Point pos = {player->position.x, player->position.y};
        prevPos = pos;

        EventDispatcher* ed = e->getSource();
        // ed->removeEventListener(this, CHANGE);

        prevS = currentS;
        currentS = nextScene;
        Game::camera->removeImmediateChild(MyGame::currentScene);
        //Transition to scene
		MyGame::currentScene = currentS;       
		Game::camera->addChild(MyGame::currentScene);
        prevCam.x = Game::camera->position.x; 
        prevCam.y = Game::camera->position.y; 
        Game::camera->position.x = 0; //reset camera position
        Game::camera->position.y = 0; 
        // Tween* newFade = new Tween(currentS);
        // TweenableParams alpha; 
        // alpha.name = "alpha"; 
        // newFade->animate(alpha, 0, 255, 3);
        // MyGame::tj->add(newFade); 
    }
    else if (e->getType() == REVERT) 
    {
        currentS = prevS;
        //if e->getEnemy()->state = "killed" or e->getEnemy()->state = "captured"
        //delete currentS->enemy.at(e->getEnemy()->id)
        currentS->isBattle = false;
        player->position = prevPos;

    }
    else if (e->getType() == REVERTBATTLE)
    {
        currentS = prevS;
        //if e->getEnemy()->state = "killed" or e->getEnemy()->state = "captured"
        //delete currentS->enemy.at(e->getEnemy()->id)
        currentS->isBattle = false;
        player->position = prevPos;
        e->getEnemy()->visible = false;
        // currentS->removeEnemy(e->getEnemy()); 

        Game::camera->removeImmediateChild(MyGame::currentScene);
        MyGame::currentScene = currentS;       
        Game::camera->addChild(MyGame::currentScene);
        Game::camera->position.x = prevCam.x; 
        Game::camera->position.y = prevCam.y; 
        
    }
}

Scene* SceneManager::getCurrentScene(){
    return this->currentS;
}