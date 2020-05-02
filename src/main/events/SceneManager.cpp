#include "SceneManager.h"
#include "Layer.h"
#include "Game.h"
#include "MyGame.h"
#include "SelectionMenu.h"
#include "RoomSave.h"
#include "MenuItem.h"
#include "RumbleEvent.h"
#include <iostream>
#include <string>
using namespace std;

SceneManager* SceneManager::instance;

SceneManager::SceneManager(Player* chara, Scene* s)
{
    currentS = s;
    player = chara;
    instance = this;
    // update collision system
    Event * e = new Event(SCENE_CHANGE_EVENT, EventDispatcher::getInstance());
    EventDispatcher::getInstance()->dispatchEvent(e);
}

SceneManager::SceneManager()
{
    instance = this;
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
        //MyGame::collisionSystem->clearAllData();
        Scene* nextScene = new Scene();
        // cout << "scene path " << e->getScenePath() << endl;
        nextScene->loadTileMap(e->getScenePath());
        int fromRm = currentS->getSceneNum(); 
        int toRm = nextScene->getSceneNum(); //room numbers of current level and next level
        //check to see if loading room for the first time 
        // if (MyGame::saveGame->savedRooms[toRm]){
        //     for (auto enemy = MyGame::saveGame->savedRooms[toRm]->enemies.rbegin(); 
        //         enemy != MyGame::saveGame->savedRooms[toRm]->enemies.rend(); enemy++) {      
                
        //         nextScene->addChild(enemy->second);
        //     }
        //     for (auto obj = MyGame::saveGame->savedRooms[toRm]->objects.rbegin(); 
        //         obj != MyGame::saveGame->savedRooms[toRm]->objects.rend(); obj++) {      
                
        //         nextScene->addChild(obj->second);
        //     }
        //     player = MyGame::saveGame->savedRooms[toRm]->player; 
        // }
        // else {
            string otherFilepath = "./resources/scenes/Room"+ to_string(toRm) + ".json"; //get filepath for enemies in scene
            nextScene->loadScene(otherFilepath);
            player = e->getPlayer();
        // } 
        //load enemies + objects

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
        else if (toRm == 4) {
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
        //MyGame::collisionSystem->watchForCollisions("player", "platform"); 
	    //MyGame::collisionSystem->watchForCollisions("player", "enemy");
        //Tween scene in
        Tween* newFade = new Tween(currentS);
        TweenableParams alpha; 
        alpha.name = "alpha";
        newFade->animate(alpha, 0, 255, 3);
        MyGame::tj->add(newFade); 
        // ed->addEventListener(this, CHANGE);
        Event * e = new Event(SCENE_CHANGE_EVENT, EventDispatcher::getInstance());
        EventDispatcher::getInstance()->dispatchEvent(e);

    }
    else if (e->getType() == FIGHT)
    {   
        // rumble
        EventDispatcher::getInstance()->dispatchEvent(new RumbleEvent(RUMBLE_EVENT, EventDispatcher::getInstance(), 0.5, 500));
        //add player and enemy turn listeners 
        //when player finishes a move, move on to enemy turn 
        prevS = currentS;
        // MyGame::collisionSystem->clearCollisionPairs();
        Scene* nextScene = new Scene();
        nextScene->inBattle = true;
        player = e->getPlayer();
        MyGame::actionMenu->decideFate = false;
        Layer* layer = new Layer(); 
        layer->scrollSpeed = 1;
        layer->addChild(e->getEnemy());
        //set action menu
        MyGame::actionMenu->getItem(0)->setAction(new Event(ATTACK, MyGame::eDispatcher, player, e->getEnemy()));
        //visability and transform choice
        if (player->possiblestates.find("ghost") == player->possiblestates.end()){
           
           MyGame::abilities->getItem(0)->visible = false; /// MyGame::actionMenu->getItem(2)->nextMenu->getItem(0)
        }
        else{
             MyGame::abilities->getItem(0)->visible = true;
            MyGame::abilities->getItem(0)->setAction(new Event(GHOST, MyGame::eDispatcher, player, e->getEnemy()));
        }
        if (player->possiblestates.find("strength") == player->possiblestates.end()){
            // MyGame::actionMenu->getItem(2)->nextMenu->getItem(0)->setAction(new Event(TRANSFORM, MyGame::eDispatcher, player, e->getEnemy()));
            MyGame::abilities->getItem(1)->visible = false; /// MyGame::actionMenu->getItem(2)->nextMenu->getItem(0)
        }
        else{
             MyGame::abilities->getItem(1)->visible = true;
            MyGame::abilities->getItem(1)->setAction(new Event(STRENGTHCOMBAT, MyGame::eDispatcher, player, e->getEnemy()));
        }
        /* if (player->possiblestates.find("ghost") != player->possiblestates.end() && player->possiblestates.find("strength") != player->possiblestates.end()){
            // MyGame::actionMenu->getItem(2)->nextMenu->removeChild(2);//->getItem(2)->nextMenu = MyGame::actionMenu;//setAction(new Event(TRAN, MyGame::eDispatcher, player, e->getEnemy()));
        } */
        MyGame::actionMenu->getItem(1)->setAction(new Event(DEFEND, MyGame::eDispatcher, player, e->getEnemy()));
        MyGame::actionMenu->getItem(3)->setAction(new Event(REVERTBATTLE, MyGame::eDispatcher, player, e->getEnemy()));
        MyGame::actionMenu->visible = true;
        enemyHP->visible = true;
        nextScene->addChild(layer);
        nextScene->setPlayer(player);
        nextScene->setEnemy(e->getEnemy());
       // turnCount++;

        SDL_Point pos = {player->position.x, player->position.y};
        prevPos = pos;

        // EventDispatcher* ed = e->getSource();
        // ed->removeEventListener(this, CHANGE);
        currentS = nextScene;
        prevCam = Game::camera->position;
        Game::camera->removeImmediateChild(MyGame::currentScene);
		MyGame::currentScene = currentS;    
		Game::camera->addChild(MyGame::currentScene);
        
        Tween* menuMove = new Tween(MyGame::actionMenu);
        Tween* enemyMove = new Tween(MyGame::currentScene->getEnemy());
        TweenableParams mfade, emove, emove2, egrowX, egrowY; 
        mfade.name = "alpha"; 
        emove.name = "position.x";
        emove2.name = "position.y";
        egrowX.name = "scaleX";
        egrowY.name = "scaleY";
        menuMove->animate(mfade, 0, 255, 5);
        // int newPosX; 
        //camera at start or end of a level 
        // if (e->getEnemy()->position.x < 400) {
        //     newPosX = (int) (Game::camera->position.x + 800)/2;
        //     cout << "beginning of level" << endl;
        // }
        // else if (e->getEnemy()->position.x > MyGame::currentScene->right + 400 &&
        //     e->getPlayer()->left){
        //     newPosX = (int) (abs(Game::camera->position.x) + 400);
        //     cout << "end of level" << endl;
        // }
        // else {
        //     newPosX = MyGame::currentScene->getPlayer()->position.x;
        // }
        // int newPosY; 
        // if (Game::camera->position.y > 0) { //render with respect to camera
        //     cout << "camera moved!"<< endl;
        //     newPosY = 400 - Game::camera->position.y;
        // }
        // else {
        //     cout << "camera not moved!" << endl;
        //     newPosY = 400; 
        // }
        int convertedX; 
        if (Game::camera->position.x > -3) { //beginning of level 
            convertedX = e->getEnemy()->position.x; 
            cout << "at beginning!" << endl;
        }
        //end of level 
        else if (Game::camera->position.x < MyGame::currentScene->right + 400
            && !e->getPlayer()->right) {
            double ratio = ((double) (e->getEnemy()->position.x)/(abs(Game::camera->position.x) + 800));
            convertedX = (int) ratio * 800; 
        }
        else {
            convertedX = 400; 
            cout << "in the middle" << endl;
        }
        //camera at end of level 
        enemyMove->animate(emove, convertedX, 400, 5);
        enemyMove->animate(emove2, e->getEnemy()->position.y, 400, 5);
        enemyMove->animate(egrowX, e->getEnemy()->scaleX, 2.5, 5);
        enemyMove->animate(egrowY, e->getEnemy()->scaleY, 2.5, 5);
        MyGame::tj->add(menuMove); 
        MyGame::tj->add(enemyMove);
        Game::camera->position = {0,0}; 
   
        Event * e = new Event(SCENE_CHANGE_EVENT, EventDispatcher::getInstance());
        EventDispatcher::getInstance()->dispatchEvent(e);
    }
    else if (e->getType() == ATTACK){
        cout<<"attack"<<endl;
        if (playerLastAction == "defend"){ //fix damage
            enemyDamage = enemyDamage*2;
        }
        if (playerLastAction == "ghost"){
            enemyDamage = baseEnemyDamage;
        }
        
         TextBox* playerturn = new TextBox(); 
         turnCount++;
        if (enemyHP->curVal < playerdamage) { //less heath than player damage
            cout << "ENEMY HEALTH DEPLETED"<<endl;
            enemyHP->curVal = 0;
            MyGame::actionMenu->selectedaitem = false;
            MyGame::eDispatcher->dispatchEvent(new Event(DEFEATEDENEMY, MyGame::eDispatcher, player, e->getEnemy()));
             cout<<"defeat enemy"<<endl;
             enemyDefeated = true;
             if (playerLastAction == "strength"){
            playerdamage = playerdamage/2;
            }
             playerLastAction="end";
            // break;
            //cout<<"selected: "<<MyGame::actionMenu->selectedaitem<<endl;  
        }
        else { //damage
       
            if (jumpAbility == false && (block != true || blockUse == 2)  && turnCount >= turnAbilityStop){ //|| abilityUse == 4) &&  && (lasting == 0 || lasting == 3)){ //check for not block, not jump, and make sure 
            //actions havent been used in a row too much, and make sure ghost isnt still happening 
                abilityUse = 0;
                blockUse =0;
                enemyHP->curVal -= playerdamage;
                turnAbilityStop = 0;
                 if (lastAction == "fog" && playerLastAction != "defend"){
                     playerturn->setText("The fog is in your lungs and its hard to get a good hit. Press SPACE to continue.");
                 }
                 else{
                     playerturn->setText("You attacked! Press SPACE to continue.");
                 }
                
            }
            else if( turnCount < turnAbilityStop){ //lasting == 1 || lasting == 2 ){
                 playerturn->setText("Your attack goes right through the enemy! Press SPACE to continue.");
            }
            else if (block == true){
                enemyHP->curVal -= playerdamage/2;
                 playerturn->setText("You attacked but it isnt very effective. Press SPACE to continue.");
            }
            else{ //do no damage 
                 playerturn->setText("Your attack seems to cause no harm! Press SPACE to continue.");
            }
            // if (lasting == 2){ //reset lasting
            //     lasting = 0;
            // }
            if (playerLastAction == "strength"){
            playerdamage = playerdamage/2;
            }
            playerLastAction = "attack";
            jumpAbility = false;
            block = false;
            MyGame::actionMenu->enemyTurn = true;
            MyGame::actionMenu->selectedaitem = false;
            //cout<<"selected: "<<MyGame::actionMenu->selectedaitem<<endl;
        }
        if (enemyHP->curVal <= 0 && enemyDefeated == false){ //player 0's enemy health
            enemyHP->curVal = 0; 
            cout << "ENEMY DEFEATED"<<endl;
            enemyHP->curVal = 0;
             if (playerLastAction == "strength"){
            playerdamage = playerdamage/2;
            }
            playerLastAction = "end";
            MyGame::eDispatcher->dispatchEvent(new Event(DEFEATEDENEMY, MyGame::eDispatcher, player, e->getEnemy()));
            cout<<"defeat enemy"<<endl;
        }
        else {
            MyGame::actionMenu->visible = false; 
            if (enemyDefeated == false){
                TextBox* playerturn = new TextBox(); 
                playerturn->setText("You attacked! Press SPACE to continue.");
                // playerturn->position.x = 0;
                MyGame::currentScene->addChild(playerturn);
                if (playerLastAction == "strength"){
                    playerdamage = playerdamage/2;
                }
                playerLastAction = "attack";
            }
            //MyGame::eDispatcher->dispatchEvent(new Event(ENEMYTURN, MyGame::eDispatcher, e->getPlayer(), e->getEnemy()));
            //cout<<"player turn over"<<endl;
        }
        //player turn over
        
    }
    else if (e->getType() == DEFEND){
         TextBox* playerturn = new TextBox(); 
         turnCount++;
        if (playerLastAction != "defend"){
            enemyDamage = enemyDamage/2;
        }
        if (playerLastAction == "ghost"){
            enemyDamage = baseEnemyDamage;
        }
        if (playerLastAction == "strength"){
            playerdamage = playerdamage/2;
        }
        playerLastAction = "defend";
        if (lastAction == "fog"){
            playerdamage = playerdamage*2;
            //enemyDamage = enemyDamage/2;
            cout<<"defend"<<endl;
            playerturn->setText("You withstood the fog! But you can't see the boss... Press SPACE to continue.");
        }
       
        MyGame::actionMenu->enemyTurn = true;
        MyGame::actionMenu->selectedaitem = false;
        MyGame::actionMenu->visible = false; 
        MyGame::currentScene->addChild(playerturn);

    }
    else if (e->getType() == GHOST){
         turnCount++;
        if (playerLastAction == "defend"){
            enemyDamage = enemyDamage*2;
        }
       if (playerLastAction == "strength"){
            playerdamage = playerdamage/2;
        }
        playerLastAction = "ghost";
        cout<<"ghost"<<endl;
        enemyDamage = enemyDamage-enemyDamage;
        TextBox* playerturn = new TextBox(); 
        playerturn->setText("You transformed into a ghost! Press SPACE to continue.");
        //MyGame::abilities->goBack();
        MyGame::actionMenu->enemyTurn = true;
        MyGame::actionMenu->visible = false; 
        MyGame::abilities->visible = false; 
        MyGame::currentScene->addChild(playerturn);
    }
     else if (e->getType() == STRENGTHCOMBAT){
          turnCount++;
        if (playerLastAction == "defend"){
            enemyDamage = enemyDamage*2;
        }
        if (playerLastAction == "ghost"){
            enemyDamage = baseEnemyDamage;
        }
        playerLastAction = "strength";
        playerdamage = playerdamage*2;
        TextBox* playerturn = new TextBox(); 
        playerturn->setText("You transformed into a bear! Press SPACE to continue.");
        MyGame::actionMenu->enemyTurn = true;
        MyGame::actionMenu->selectedaitem = false;
        MyGame::actionMenu->visible = false; 
        MyGame::currentScene->addChild(playerturn);
    }
    else if (e->getType() == ENEMYTURN) {
        //if (lasting )
         
        //  cout<<"cooldown: "<<cooldown<<endl;
        //  if (cooldown == 0){ //rest cooldown
        //      cooldown = 4;
        //  }
        //  if (cooldown <= 3){ //decrease cooldown
        //     cooldown--;
        // }
        TextBox* enemyattack = new TextBox();
        string id = MyGame::currentScene->getEnemy()->id;
        id.pop_back();
        if (id == "boss"){
                 int choose = rand() % 100; 

               if (choose < 33){ //use fog
                    playerdamage = playerdamage/2;
                    enemyDamage = enemyDamage*2;
                     enemyattack->setText("A huge wave of fog is about to chrash into you! Press C to continue.");
                    MyGame::currentScene->addChild(enemyattack);
                    turnAbilityUse = turnCount + 8;
                    turnAbilityStop = turnCount+4;
                    lastAction = "fog";
               }
               else if (choose >= 33 && choose < 66){ //defend
                 cout<<"block"<<endl;
                block = true;
                // if(lasting > 0){ //if we are still seeing how long abilities last, increase lasting
                //      lasting++;
                // }
                // if (lasting  == 2){ //if its the end of the ability lasting, start cooldown
                //         cooldown--;
                //     }
                if(lastAction == "block"){ //check for same action in a row
                    blockUse++;
                }
                else if (blockUse == 0){

                }
                else{
                    blockUse--;
                }
                cout<<"block use: "<<blockUse<<endl;
                if (blockUse >= 2){ //if the enemy has tried to use block 3 times in a row 
                    if (blockUse >= 3){ //rest block if over 3 attempts
                        blockUse = 0;
                    }
                    enemyattack->setText("The enemy tried and failed to use block! Press C to continue.");
                    //blockUse
                    //blockUse = 0;
                }
                else{
                    enemyattack->setText("The enemy blocked! Press C to continue.");
                
                }
                // enemyattack->position.x = 0;
                MyGame::currentScene->addChild(enemyattack);
                lastAction = "block";
               }
               else{ //if (choose >= 50 && choose < 75){//normal attack 
                cout<<"use attack"<<endl;
                    if (playerHP->curVal-enemyDamage <= 0){
                    MyGame::currentScene->dead = true;
                    MyGame::eDispatcher->dispatchEvent(new Event(DEATH, MyGame::eDispatcher, player, e->getEnemy()));  
                    lastAction = "";          
                    }
                    else{
                        playerHP->curVal-=enemyDamage;  
                        if (lastAction == "fog" || turnCount - turnAbilityStop > 0){
                             enemyattack->setText("The enemy attacked back with more force in the fog! Press C to continue.");
                        }
                        else{
                             enemyattack->setText("The enemy attacked back! Press C to continue.");
                        }
                   
                    // enemyattack->position.x = 0;
                    MyGame::currentScene->addChild(enemyattack);
                    lastAction = "attack";
                    
                    }
               }
            
        }     

        else{
            
             int choose = rand() % 100; 
            if ( turnAbilityUse > turnCount){// } <= 3 && (choose > 33 && choose <= 66)){ //choose another ability b/c ability is on cooldown
                choose = rand() % 100; 
                if (choose >= 64){
                    choose = 88;
                    cout<<"choose block"<<endl;
                }
                else{
                    choose = 23;
                    cout<<"choose attack"<<endl;
                }
            }
            //if (turnAbilityUse )
            cout<<choose<<endl;
            if (choose <= 33){ 
                //attack
                cout<<"use attack"<<endl;
                if (playerHP->curVal-enemyDamage <= 0){
                MyGame::currentScene->dead = true;
                MyGame::eDispatcher->dispatchEvent(new Event(DEATH, MyGame::eDispatcher, player, e->getEnemy()));  
                lastAction = "";          
                }
                else{
                    playerHP->curVal-=enemyDamage;  
                // if(lasting > 0){ //if the old ability is still lasting,
                //      lasting++;
                //      if (lasting  == 2){ //if the end of the ability lasting decrease cooldown
                //         cooldown--;
                //     }
                // } 
                enemyattack->setText("The enemy attacked back! Press C to continue.");
                // enemyattack->position.x = 0;
                MyGame::currentScene->addChild(enemyattack);
                lastAction = "attack";
                
                }
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
                
                if (id == "frog"){ //if its a frog use jump
                    jumpAbility = true;
                    turnAbilityUse = turnCount + 4;
                    turnAbilityStop = turnCount+2;
                    enemyattack->setText("The enemy jumped up high! Press C to continue.");
                    // if (cooldown <= 4){ //start cooldown
                    //     cooldown--;
                    // }
                }
                else if (id == "ghost"){ //if its a ghost
                    ghostAbility = true;
                    turnAbilityUse = turnCount+8;
                    turnAbilityStop = turnCount+4;
                    // lasting++; //add to duration
                    // if (lasting  == 2){ //if its the end of the duration, start cooldown 
                    //     cooldown--;
                    // }
                    enemyattack->setText("The enemy is transparent! Press C to continue.");
                }
                else if (id == "bear"){ //if its a ghost
                    //ghostAbility = true;
                    turnAbilityUse = turnCount+8;
                    turnAbilityStop = turnCount+4;
                    enemyDamage = enemyDamage*2;
                    //playerdamage = playerdamage/2;
                    // lasting++; //add to duration
                    // if (lasting  == 2){ //if its the end of the duration, start cooldown 
                    //     cooldown--;
                    // }
                    enemyattack->setText("The enemy is huge! Press C to continue.");
                }
                //cout<<id<<endl; 
                if (abilityUse == 4){ //if abilities has been used 4 times in a row
                    enemyattack->setText("The enemy tried and failed to use an ability! Press C to continue.");
                }
                
                //enemyattack->setText("The enemy used an ability! Press C to continue.");
                // enemyattack->position.x = 0;
                MyGame::currentScene->addChild(enemyattack);
                lastAction = "ability";        
            }
            else{
                cout<<"block"<<endl;
                block = true;
                // if(lasting > 0){ //if we are still seeing how long abilities last, increase lasting
                //      lasting++;
                // }
                // if (lasting  == 2){ //if its the end of the ability lasting, start cooldown
                //         cooldown--;
                //     }
                if(lastAction == "block"){ //check for same action in a row
                    blockUse++;
                }
                else if (blockUse == 0){

                }
                else{
                    blockUse--;
                }
                cout<<"block use: "<<blockUse<<endl;
                if (blockUse >= 2){ //if the enemy has tried to use block 3 times in a row 
                    if (blockUse >= 3){ //rest block if over 3 attempts
                        blockUse = 0;
                    }
                    enemyattack->setText("The enemy tried and failed to use block! Press C to continue.");
                    //blockUse
                    //blockUse = 0;
                }
                else{
                    enemyattack->setText("The enemy blocked! Press C to continue.");
                
                }
                // enemyattack->position.x = 0;
                MyGame::currentScene->addChild(enemyattack);
                lastAction = "block";
            }
        }
       
       MyGame::actionMenu->enemyTurn = false;
       cout<<"END OF ENEMY TURN"<<endl;
    
        //enemy turn over
    }
    else if (e->getType() == DEFEATEDENEMY) {
        cout << "u defeated the enemy!"<< endl;
        MyGame::actionMenu->visible = false;
        string id = MyGame::currentScene->getEnemy()->id;
        id.pop_back();
         TextBox* victoryMSG = new TextBox(); 
        if (id == "fakeboss"){
            victoryMSG->setText("Congrats! But your boss is somewhere else. Go find him!");
            MyGame::actionMenu->decideFate = false; 
             MyGame::actionMenu->fakeboss = true; 
             
        }
        else if (id == "boss"){
            MyGame::actionMenu->decideFate = true; 
            victoryMSG->setText("Congrats, you defeated the boss! Press Tab to decide the enemy's fate.");
        }
        else{
            MyGame::actionMenu->decideFate = true; 
            victoryMSG->setText("Congrats, you won! Press Tab to decide the enemy's fate.");
        }

        victoryMSG->visible = true;
        MyGame::currentScene->addChild(victoryMSG);

    }
     else if (e->getType() == DECIDEFATE) {
        cout << "inside decide fate event"<<endl;
        string id = MyGame::currentScene->getEnemy()->id;
        id.pop_back();
        MyGame::actionMenu->visible = false;
        MyGame::enemyFate->visible = true;
        MyGame::enemyFate->getItem(0)->setAction(new Event(SPARE, MyGame::eDispatcher, player, e->getEnemy()));
        MyGame::enemyFate->getItem(1)->setAction(new Event(KILL, MyGame::eDispatcher, player, e->getEnemy()));
        
        if (id == "frog" && player->possiblestates.find("frog") == player->possiblestates.end()){
             MyGame::enemyFate->getItem(2)->setAction(new Event(CONSUME, MyGame::eDispatcher, player, e->getEnemy()));
        }
        else if (id == "ghost" && player->possiblestates.find("ghost") == player->possiblestates.end()){
             MyGame::enemyFate->getItem(2)->setAction(new Event(CONSUME, MyGame::eDispatcher, player, e->getEnemy()));
        }
        else{
            MyGame::enemyFate->removeChild(2);
        }
       
    }
    else if (e->getType() == SPARE) {
        //Same as Revert battle basically
        //character stuff 
        player->num_enemies_spared ++;
        e->setType(REVERTBATTLE);
    }
    else if (e->getType() == KILL) {
        player->num_enemies_killed ++;
        e->setType(REVERTBATTLE);
    }
    else if (e->getType() == CONSUME) {
        string id = MyGame::currentScene->getEnemy()->id;
        id.pop_back();
        if (id == "ghost"){
            if (player->possiblestates.size() == 0){
               MyGame::abilities->removeChild(2);
            }
            player->possiblestates.insert("ghost");
        }
        if (id == "frog"){
             if (player->possiblestates.size() == 0){
                MyGame::abilities->removeChild(2);
            }
            player->possiblestates.insert("frog");
        }
        e->setType(REVERTBATTLE);
    }
    else if (e->getType() == REVERT) 
    {
        //currentS = prevS;
                 //if e->getEnemy()->state = "killed" or e->getEnemy()->state = "captured"
                    //delete currentS->enemy.at(e->getEnemy()->id)
        //currentS->isBattle = false;
       // player->position = prevPos;
       cout<<"Reset"<<endl;
        playerHP->curVal = 100;
        currentS = startS;
        currentS->isBattle = false;
        player = e->getPlayer();
        player->position = startPos;
        player->enemy = NULL;
        player->inBattle = false;
        currentS->setPlayer(player);
        currentS->setEnemy(NULL);
        MyGame::actionMenu->visible = false;
        MyGame::abilities->visible = false;
        MyGame::enemyFate->visible = false;
        MyGame::actionMenu->selectInd = 0;
        e->getEnemy()->visible = false;
        enemyHP->visible = false;
        enemyHP->curVal = enemyHP->maxVal;
       
        //e->getEnemy()->gameType = "defeated"; //so player doesn't collide with it again
        //e->getEnemy()->position.x = e->getEnemy()->prevPos;
        //e->getEnemy()->scaleX = e->getEnemy)()->prevPos;
        //e->getEnemy()->scaleY = e->getEnemy)()->prevPos;
        Game::camera->removeImmediateChild(MyGame::currentScene);  
        //currentS->loadTileMap("./resources/scenes/area1files/Area1Room7.json");
	    currentS->loadScene("./resources/scenes/Room7.json");     
        MyGame::currentScene = currentS;
        Game::camera->addChild(MyGame::currentScene);
        Game::camera->position.x = 0;
        //delete MyGame::scene1;
        // MyGame::collisionSystem->watchForCollisions("player", "platform"); 
	    // MyGame::collisionSystem->watchForCollisions("player", "enemy");
        jumpAbility = false;
        block = false;
        abilityUse = 0;
        enemyDefeated = false;
        blockUse = 0;
        ghostAbility = false;
        turnCount = 0; //the current turn #
        turnAbilityUse = 0; // turn where ability can be used again
        turnAbilityStop = 0; //turn where ability stops being used;
        lastAction = "";
        Event * e = new Event(SCENE_CHANGE_EVENT, EventDispatcher::getInstance());
        EventDispatcher::getInstance()->dispatchEvent(e);
    }
    else if (e->getType() == DEATH){
        playerHP->curVal = 0;
        TextBox* playerturn = new TextBox(); 
        playerturn->setText("You have died. Press 1 to be returned to the dream. Good Luck!");
        //MyGame::abilities->goBack();
        MyGame::actionMenu->death = true;
        MyGame::actionMenu->visible = false; 
        MyGame::abilities->visible = false; 
        MyGame::currentScene->addChild(playerturn);
    }
    if (e->getType() == REVERTBATTLE)
    {
        //if e->getEnemy()->state = "killed" or e->getEnemy()->state = "captured"
        //delete currentS->enemy.at(e->getEnemy()->id)
        // currentS->getEnemy()->gameType = "defeated";
        currentS = prevS;
        currentS->isBattle = false;
        player = e->getPlayer();
        player->position = prevPos;
        player->enemy = NULL;
        player->inBattle = false;
        currentS->setPlayer(player);
        currentS->setEnemy(NULL);
        MyGame::actionMenu->visible = false;
        MyGame::enemyFate->visible = false;
        MyGame::actionMenu->selectInd = 0;
        e->getEnemy()->visible = false;
        enemyHP->visible = false;
        enemyHP->curVal = enemyHP->maxVal;
        e->getEnemy()->gameType = "defeated"; //so player doesn't collide with it again
        // currentS->removeEnemy(e->getEnemy()->id);
        Game::camera->position = prevCam;
        Game::camera->removeImmediateChild(MyGame::currentScene);
        MyGame::currentScene = currentS;       
        Game::camera->addChild(MyGame::currentScene);
        // MyGame::collisionSystem->watchForCollisions("player", "platform"); 
	    // MyGame::collisionSystem->watchForCollisions("player", "enemy");
        jumpAbility = false;
        block = false;
        abilityUse = 0;
        enemyDefeated = false;
        blockUse = 0;
        ghostAbility = false;
        turnCount = 0; //the current turn #
        turnAbilityUse = 0; // turn where ability can be used again
        turnAbilityStop = 0; //turn where ability stops being used;
        lastAction = "";
        Event * e = new Event(SCENE_CHANGE_EVENT, EventDispatcher::getInstance());
        EventDispatcher::getInstance()->dispatchEvent(e);
    }
}

Scene* SceneManager::getCurrentScene(){
    return this->currentS;
}


SceneManager* SceneManager::getInstance(){
    if (!instance){
        instance = new SceneManager();
    }
    return instance;
}