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
        cout << "in fight" << endl;
    }
    else if (e->getType() == ATTACK){
        if (enemyHP->curVal < 50) {
            cout << "ENEMY HEALTH DEPLETED"<<endl;
            enemyHP->curVal = 0;
            MyGame::actionMenu->selectedaitem = false;
            MyGame::eDispatcher->dispatchEvent(new Event(DEFEATEDENEMY, MyGame::eDispatcher, player, e->getEnemy()));
            //cout<<"selected: "<<MyGame::actionMenu->selectedaitem<<endl;  
        }
        else {
            //cout<<"enemy"<<endl;
            if ((jumpAbility == false || abilityUse == 4 || blockUse == 6) && block != true){ //check for not block, not jump, and make sure 
            //actions havent been used in a row too much
                abilityUse = 0;
                blockUse =0;
                enemyHP->curVal -= 10;
            }
            if (block == true){
                enemyHP->curVal -= 50;
            }
            jumpAbility = false;
            block = false;
            MyGame::actionMenu->enemyTurn = true;
            MyGame::actionMenu->selectedaitem = false;
            //cout<<"selected: "<<MyGame::actionMenu->selectedaitem<<endl;
        }
        if (enemyHP->curVal <= 0){
            enemyHP->curVal = 0; 
            cout << "ENEMY DEFEATED"<<endl;
            enemyHP->curVal = 0;
            MyGame::actionMenu->selectedaitem = false;
            MyGame::eDispatcher->dispatchEvent(new Event(DEFEATEDENEMY, MyGame::eDispatcher, player, e->getEnemy()));
        }
        else {
            MyGame::actionMenu->visible = false; 
            TextBox* playerturn = new TextBox(); 
            playerturn->setText("You attacked! Press SPACE to continue.");
            MyGame::currentScene->addChild(playerturn);
            //MyGame::eDispatcher->dispatchEvent(new Event(ENEMYTURN, MyGame::eDispatcher, e->getPlayer(), e->getEnemy()));
            cout<<"player turn over"<<endl;
        }
        //player turn over
    }
    else if (e->getType() == ENEMYTURN) {
        int choose = rand() % 100; 
        if (choose <= 33){
            cout<<"use attack"<<endl;
             playerHP->curVal-=5;  
             TextBox* enemyattack = new TextBox(); 
            enemyattack->setText("The enemy attacked back! Press C to continue.");
             MyGame::currentScene->addChild(enemyattack);
             lastAction = "attack";
             
        }
        else if (choose > 33 && choose <= 66){
            //use ability 
            cout<<"use ability"<<endl;
            if (lastAction == "ability"){//check for same action in a row
                abilityUse ++;
            }
            else{
                abilityUse--;
            }
            string id = MyGame::currentScene->getEnemy()->id;
            cout<<id<<endl;
            jumpAbility = true;
            TextBox* enemyattack = new TextBox(); 
            if (abilityUse == 4){
                enemyattack->setText("The enemy tried and failed to use an ability! Press C to continue.");
            }
            enemyattack->setText("The enemy used an ability! Press C to continue.");
            MyGame::currentScene->addChild(enemyattack);
            lastAction = "ability";
            
        }
        else{
            cout<<"block"<<endl;
            block = true;
            if(lastAction == "block"){ //check for same action in a row
                blockUse++;
            }
            else{
                blockUse--;
            }
             TextBox* enemyattack = new TextBox(); 
             if (blockUse == 4){
                enemyattack->setText("The enemy tried and failed to use block! Press C to continue.");
            }
            enemyattack->setText("The enemy blocked! Press C to continue.");
            MyGame::currentScene->addChild(enemyattack);
             lastAction = "block";
        }
       MyGame::actionMenu->enemyTurn = false;
    
        //enemy turn over
        //how to remove/change actionMenu??? use the same menu but change the options?? 
        
        // Game::camera->removeImmediateChild(MyGame::currentScene);
        // MyGame::currentScene->removeImmediateChild(enemyattack);    
		// Game::camera->addChild(MyGame::currentScene);
        // MyGame::actionMenu->visible = true;
        // MyGame::actionMenu->visible = true; 
    }
    else if (e->getType() == DEFEATEDENEMY) {
        cout << "u defeated the enemy!"<< endl;
        MyGame::actionMenu->visible = false;
        MyGame::actionMenu->decideFate = true; 
        TextBox* victoryMSG = new TextBox(); 
        victoryMSG->setText("Congrats, you won! Press Enter to decide the enemy's fate.");
        victoryMSG->visible = true;
        MyGame::currentScene->addChild(victoryMSG);

    }
     else if (e->getType() == DECIDEFATE) {
         cout << "inside decide fate event"<<endl;
        MyGame::actionMenu->visible = false;
        MyGame::enemyFate->visible = true;

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