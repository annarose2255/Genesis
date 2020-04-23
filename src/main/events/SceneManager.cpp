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
        //add player and enemy turn listeners 
        //when player finishes a move, move on to enemy turn 
        Scene* nextScene = new Scene();
        nextScene->inBattle = true;
        //don't load in character, save it from the previous scene
        //set it back in revert 
        //get Player instead of character??
        player = e->getPlayer();
    
        e->getEnemy()->position.x = 400;
        e->getEnemy()->position.y = 400;
        
        Layer* layer = new Layer(); 
        layer->scrollSpeed = 1;
        layer->addChild(e->getEnemy());
        //set action menu
        MyGame::actionMenu->getItem(0)->setAction(new Event(ATTACK, MyGame::eDispatcher, player, e->getEnemy()));
        MyGame::actionMenu->getItem(3)->setAction(new Event(REVERTBATTLE, MyGame::eDispatcher, player, e->getEnemy()));
        MyGame::actionMenu->visible = true;
        enemyHP->visible = true;
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
        Tween* menuMove = new Tween(MyGame::actionMenu);
        Tween* enemyMove = new Tween(MyGame::currentScene->getEnemy());
        TweenableParams mfade, emove, egrowX, egrowY; 
        mfade.name = "alpha"; 
        emove.name = "position.x";
        egrowX.name = "scaleX";
        egrowY.name = "scaleY";
        menuMove->animate(mfade, 0, 255, 5);
        enemyMove->animate(emove, 800, MyGame::currentScene->getEnemy()->position.x, 5);
        enemyMove->animate(egrowX, MyGame::currentScene->getEnemy()->scaleX, 2.5, 5);
        enemyMove->animate(egrowY, MyGame::currentScene->getEnemy()->scaleY, 2.5, 5);
        MyGame::tj->add(menuMove); 
        MyGame::tj->add(enemyMove); 
    }
    else if (e->getType() == ATTACK){
        if (enemyHP->curVal < 10) {
            enemyHP->curVal = 0;
        }
        else {
            enemyHP->curVal -= 10;
        }
        if (enemyHP->curVal == 0) {
            //add another menu to allow character to select consume, spare, kill
        }
        // MyGame::actionMenu->visible = false; 
        // MyGame::eDispatcher->dispatchEvent(new Event(ENEMYTURN, MyGame::eDispatcher, e->getPlayer(), e->getEnemy()));
        //player turn over
    }
    else if (e->getType() == ENEMYTURN) {
        playerHP->curVal-=5;  
        // TextBox* enemyattack = new TextBox(); 
        // enemyattack->setText("The enemy attacked back!");
        //enemy turn over
        //how to remove/change actionMenu??? use the same menu but change the options?? 
        MyGame::actionMenu->visible = true; 
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
        MyGame::actionMenu->visible = false;
        MyGame::actionMenu->selectInd = 0;
        e->getEnemy()->visible = false;
        enemyHP->visible = false;
        enemyHP->curVal = enemyHP->maxVal;
        e->getEnemy()->gameType = "defeated"; //so player doesn't collide with it again

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