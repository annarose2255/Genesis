#include "SceneManager.h"
#include "Layer.h"
#include "Game.h"
#include "MyGame.h"
#include "SelectionMenu.h"
#include "MenuItem.h"
#include <iostream>
#include <string>
using namespace std;
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
        cout << "scene path " << e->getScenePath() << endl;
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
        prevS = currentS;
        MyGame::collisionSystem->clearCollisionPairs();
        Scene* nextScene = new Scene();
        nextScene->inBattle = true;
        player = e->getPlayer();

        Layer* layer = new Layer(); 
        layer->scrollSpeed = 1;
        layer->addChild(e->getEnemy());
        //set action menu
        MyGame::actionMenu->getItem(0)->setAction(new Event(ATTACK, MyGame::eDispatcher, player, e->getEnemy()));
        //visability and transform choice
        
        if (player->possiblestates.find("ghost") == player->possiblestates.end()){
            if (MyGame::abilities->numChildren() == 2){
                MyGame::abilities->getItem(0)->visible = false; /// MyGame::actionMenu->getItem(2)->nextMenu->getItem(0)
            }
            else{
                MyGame::abilities->getItem(1)->visible = false; 
            }
           //MyGame::abilities->getItem(0)->
        }
        else{
            if (MyGame::abilities->numChildren() == 2){
                MyGame::abilities->getItem(0)->visible = true; 
                cout<<"action ghost"<<endl;
                MyGame::abilities->getItem(0)->setAction(new Event(GHOST, MyGame::eDispatcher, player, e->getEnemy()));
            }
            else{
                MyGame::abilities->getItem(1)->visible = true; 
                cout<<"action ghost2"<<endl;
                MyGame::abilities->getItem(1)->setAction(new Event(GHOST, MyGame::eDispatcher, player, e->getEnemy()));
            }
        }
        if (player->possiblestates.find("strength") == player->possiblestates.end()){
            // MyGame::actionMenu->getItem(2)->nextMenu->getItem(0)->setAction(new Event(TRANSFORM, MyGame::eDispatcher, player, e->getEnemy()));
             /// MyGame::actionMenu->getItem(2)->nextMenu->getItem(0)
             if (MyGame::abilities->numChildren() == 2){
                MyGame::abilities->getItem(1)->visible = false; 
            }
            else{
                MyGame::abilities->getItem(2)->visible = false; 
            }
        }
        else{
             if (MyGame::abilities->numChildren() == 2){
                MyGame::abilities->getItem(1)->visible = true; 
                MyGame::abilities->getItem(1)->setAction(new Event(GHOST, MyGame::eDispatcher, player, e->getEnemy()));
            }
            else{
                MyGame::abilities->getItem(2)->visible = true; 
                MyGame::abilities->getItem(2)->setAction(new Event(STRENGTHCOMBAT, MyGame::eDispatcher, player, e->getEnemy()));
            }
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
        int newPosX; 
        //camera at start or end of a level 
        if (e->getEnemy()->position.x < 800) {
            newPosX = (int) (Game::camera->position.x + 800)/2;
        }
        else if (e->getEnemy()->position.x > MyGame::currentScene->right + 800){
            newPosX = (int) (abs(Game::camera->position.x) + 400);
        }
        else {
            newPosX = MyGame::currentScene->getPlayer()->position.x;
        }
        int newPosY; 
        if (Game::camera->position.y > 0) { //render with respect to camera
            cout << "camera moved!"<< endl;
            newPosY = 400 - Game::camera->position.y;
        }
        else {
            cout << "camera not moved!" << endl;
            newPosY = 400; 
        }
        //camera at end of level 
        enemyMove->animate(emove, e->getEnemy()->position.x, newPosX, 5);
        enemyMove->animate(emove2, e->getEnemy()->position.y, newPosY, 5);
        enemyMove->animate(egrowX, e->getEnemy()->scaleX, 2.5, 5);
        enemyMove->animate(egrowY, e->getEnemy()->scaleY, 2.5, 5);
        MyGame::tj->add(menuMove); 
        MyGame::tj->add(enemyMove); 
    }
    else if (e->getType() == ATTACK){
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
                playerturn->setText("You attacked! Press SPACE to continue.");
            }
            else if( turnCount < turnAbilityStop){ //lasting == 1 || lasting == 2 ){
                 playerturn->setText("You attack goes right through the enemy! Press SPACE to continue.");
            }
            else if (block == true){
                enemyHP->curVal -= playerdamage/2;
                 playerturn->setText("You attacked but it isnt very effective. Press SPACE to continue.");
            }
            else{ //do no damage 
                 playerturn->setText("You attack seems to cause no harm! Press SPACE to continue.");
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
            MyGame::actionMenu->selectedaitem = false;
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
        TextBox* playerturn = new TextBox(); 
        cout<<"defend"<<endl;
        playerturn->setText("You defended! Press SPACE to continue.");
        MyGame::actionMenu->enemyTurn = true;
        MyGame::actionMenu->selectedaitem = false;
        MyGame::actionMenu->visible = false; 
        MyGame::currentScene->addChild(playerturn);

    }
    else if (e->getType() == GHOST){
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
        MyGame::abilities->goBack();
        MyGame::actionMenu->enemyTurn = true;
        MyGame::actionMenu->selectedaitem = false;
        MyGame::actionMenu->visible = false; 
        MyGame::currentScene->addChild(playerturn);
    }
     else if (e->getType() == STRENGTHCOMBAT){
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
         TextBox* enemyattack = new TextBox(); 
        //  cout<<"cooldown: "<<cooldown<<endl;
        //  if (cooldown == 0){ //rest cooldown
        //      cooldown = 4;
        //  }
        //  if (cooldown <= 3){ //decrease cooldown
        //     cooldown--;
        // }
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
             playerHP->curVal-=enemyDamage;  
            // if(lasting > 0){ //if the old ability is still lasting,
            //      lasting++;
            //      if (lasting  == 2){ //if the end of the ability lasting decrease cooldown
            //         cooldown--;
            //     }
            // } 
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
            id.pop_back();
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
            //cout<<id<<endl; 
            if (abilityUse == 4){ //if abilities has been used 4 times in a row
                enemyattack->setText("The enemy tried and failed to use an ability! Press C to continue.");
            }
            
            //enemyattack->setText("The enemy used an ability! Press C to continue.");
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
            
            MyGame::currentScene->addChild(enemyattack);
            lastAction = "block";
        }
       MyGame::actionMenu->enemyTurn = false;
       cout<<"END OF ENEMY TURN"<<endl;
    
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
        victoryMSG->setText("Congrats, you won! Press Tab to decide the enemy's fate.");
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
               MyGame::abilities->removeChild(0);
            }
            player->possiblestates.insert("ghost");
        }
        if (id == "frog"){
             if (player->possiblestates.size() == 0){
                MyGame::abilities->removeChild(0);
            }
            player->possiblestates.insert("frog");
        }
        e->setType(REVERTBATTLE);
    }
    else if (e->getType() == REVERT) 
    {
        currentS = prevS;
        //if e->getEnemy()->state = "killed" or e->getEnemy()->state = "captured"
        //delete currentS->enemy.at(e->getEnemy()->id)
        currentS->isBattle = false;
        player->position = prevPos;

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
        //e->getEnemy()->position.x = e->getEnemy()->prevPos;
        //e->getEnemy()->scaleX = e->getEnemy)()->prevPos;
        //e->getEnemy()->scaleY = e->getEnemy)()->prevPos;
        Game::camera->removeImmediateChild(MyGame::currentScene);
        MyGame::currentScene = currentS;       
        Game::camera->addChild(MyGame::currentScene);
        MyGame::collisionSystem->watchForCollisions("player", "platform"); 
	    MyGame::collisionSystem->watchForCollisions("player", "enemy");
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
    }
}

Scene* SceneManager::getCurrentScene(){
    return this->currentS;
}