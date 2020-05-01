#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Sprite.h"
#include "Scene.h"
#include "MyGame.h"
#include "Camera.h"
#include "QuestDemo.h"
#include "QuestManager.h"
#include "Tween.h"
#include "TweenableParams.h"
#include "TweenJuggler.h"
#include "HealthBar.h"
#include "SelectionMenu.h"
#include "MenuItem.h"
#include "Controls.h"

using namespace std;

EventDispatcher* MyGame::eDispatcher = EventDispatcher::getInstance();
Scene* MyGame::currentScene = new Scene();
TweenJuggler* MyGame::tj = new TweenJuggler();
CollisionSystem* MyGame::collisionSystem = new CollisionSystem();
Controls* MyGame::controls = new Controls();
SelectionMenu* MyGame::actionMenu = new SelectionMenu();
SelectionMenu* MyGame::decision = new SelectionMenu(); 
SelectionMenu* MyGame::abilities = new SelectionMenu();
SelectionMenu* MyGame::enemyFate = new SelectionMenu(); 

MyGame::MyGame() : Game(800, 700) { //rendered space
	cout << "past declarations" << endl;
	instance = this;
    scene1 = new Scene();
    // scene1->loadScene("./resources/scenes/character.json");
	scene1->loadTileMap("./resources/scenes/area1files/Area1Room7.json");
	scene1->loadScene("./resources/scenes/ghostchar.json");
	scene1->loadScene("./resources/scenes/Room7.json"); //contains objects and enemies
	//test playable char
	// AnimatedSprite* chara = new AnimatedSprite("chara"); 
	// chara->addSSAnimation("./resources/ghostchar/idle.png", "./resources/ghostchar/idle.xml");
	// chara->play("Idle");
    // chara->position = {70, 200};
	// Game::camera->addChild(chara);

    currentScene = scene1;
	sceneStart = new Scene();
	sceneStart = scene1;
    // UI Components
    // hp = new HealthBar(0, 100, 0);
    tBox = new TextBox();
    tBox->setText("Hello World !");
    tBox->visible = false;
    mainMenu = new SelectionMenu();
    MenuItem* items = new MenuItem("Items", 0, 0);
    MenuItem* save = new MenuItem("Save", 250, 0);
    MenuItem* settings = new MenuItem("Settings", 500, 0);

    itemsMenu = new SelectionMenu();
    MenuItem* healthPotion = new MenuItem("Health Potion", 0, 0);
    items->nextMenu = itemsMenu;

    actionMenu->position.y = 600;
	attack = new MenuItem("Attack", 0, 0);
	defend = new MenuItem("Defend", 0, 50);
	transform = new MenuItem("Transform", 399, 0);
	flee = new MenuItem("Flee", 399, 50);
    actionMenu->addItem(attack);
	actionMenu->addItem(defend);
    actionMenu->addItem(transform);
    actionMenu->addItem(flee);
    abilities->position.y = 600;

	enemyFate->position.y = 600;
	spare = new MenuItem("Spare", 0, 0);
	kill = new MenuItem("Kill", 250, 0);
	consume = new MenuItem("Consume", 500, 0);
	enemyFate->addItem(spare);
	enemyFate->addItem(kill);
	enemyFate->addItem(consume);
	enemyFate->visible = false;

    //if statements with each ability!!
	
    MenuItem* ghost = new MenuItem("Ghost", 10, 10);
	ghost->width = 150;
    abilities->addItem(ghost);
	//MenuItem* doubleJump = new MenuItem("Frog (Double jump)", 350, 10);
	//doubleJump->width = 400;
   // abilities->addItem(doubleJump);
	MenuItem* strength = new MenuItem("strength", 350, 10);
    abilities->addItem(strength);
	MenuItem* none = new MenuItem("NO ABILITIES", 350, 10);
    abilities->addItem(none);
	
	//none->nextMenu = transform;
	//none->prevMenu = transform;
	transform->nextMenu = abilities; 

    mainMenu->addItem(items);
    mainMenu->addItem(save);
    mainMenu->addItem(settings);
    itemsMenu->addItem(healthPotion);
    mainMenu->id = "Main";
    itemsMenu->id = "items";
    mainMenu->visible = false;
	
	hp = new HealthBar(0,100,0);
	enemyHP = new HealthBar(0,100,0);
	hp->position = { 100, 100 };
	enemyHP->position = {600, 100};
	Game::camera->position.x = 0;
	Game::camera->addChild(currentScene);
	instance->addChild(Game::camera);
	instance->addChild(tBox);
	instance->addChild(mainMenu);
	instance->addChild(actionMenu); //try child of scene or camera
	instance->addChild(abilities);
	instance->addChild(enemyFate);
	instance->addChild(itemsMenu);
	instance->addChild(hp);
	instance->addChild(enemyHP);
	// hp->visible = true;
	enemyHP->visible = false;
    //Sound 
	mainMusic = new Sound();
	//Collision Detection 
	collisionSystem->watchForCollisions("player", "platform"); 
	collisionSystem->watchForCollisions("player", "enemy");
	// set up collision system before scene manager is called
	// EventDispatcher::getInstance()->addEventListener(collisionSystem, DO_ADDED_EVENT);
	//EventDispatcher::getInstance()->addEventListener(this, DO_REMOVED_EVENT);
	EventDispatcher::getInstance()->addEventListener(collisionSystem, SCENE_CHANGE_EVENT);
	//Change Scene 
	sm = new SceneManager(currentScene->getPlayer(), currentScene);
	sm->playerHP = hp; 
	sm->enemyHP = enemyHP;
	sm->startS = sceneStart;

	sm->startPos = currentScene->getPlayer()->position;
	sm->startCam = Game::camera->position;
	
	eDispatcher = EventDispatcher::getInstance();
	eDispatcher->addEventListener(sm, CHANGE);
	eDispatcher->addEventListener(sm, FIGHT);
	eDispatcher->addEventListener(sm, ATTACK);
	eDispatcher->addEventListener(sm, REVERT);
	eDispatcher->addEventListener(sm, REVERTBATTLE);
	eDispatcher->addEventListener(sm, ENEMYTURN);
	eDispatcher->addEventListener(sm, DEFEATEDENEMY);
	eDispatcher->addEventListener(sm, DECIDEFATE);
	eDispatcher->addEventListener(sm, SPARE);
	eDispatcher->addEventListener(sm, KILL);
	eDispatcher->addEventListener(sm, CONSUME);
	eDispatcher->addEventListener(sm, DEFEND);
	eDispatcher->addEventListener(sm, TRANSFORM);
	eDispatcher->addEventListener(sm, GHOST);
	eDispatcher->addEventListener(sm, STRENGTHCOMBAT);
	eDispatcher->addEventListener(sm, DEATH);
	//eDispatcher->addEventListener(sm, )
	
	//Tween
	currentScene->getPlayer()->play("Idle");
	
	Tween* charTween = new Tween(currentScene->getPlayer());
	TweenableParams chalpha;
	chalpha.name = "alpha";
	charTween->animate(chalpha, 0, 255, 3); 
	tj->add(charTween);
	cout << "end constructor" << endl;
}

MyGame::~MyGame(){
	delete currentScene; 
	delete tj; 
	delete eDispatcher;
}

void MyGame::update(set<SDL_Scancode> pressedKeys, set<SDL_GameControllerButton> pressedButtons, set<pair<SDL_GameControllerAxis, float>> movedAxis){
	mainMenu->update(pressedKeys, pressedButtons, movedAxis);
    itemsMenu->update(pressedKeys, pressedButtons, movedAxis);
	hp->update(pressedKeys);
	enemyHP->update(pressedKeys);
	controls->key(pressedKeys,pressedButtons,movedAxis);
    // if(pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end() && change) {
    //     cout << "abc" << endl;
    //     Game::camera->removeImmediateChild(currentScene);
    //     cout << instance->children.size() << endl;
    //     currentScene = scene2;
    //     Game::camera->addChild(currentScene);
    //     change = !change;
    // }
    // else if(pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end() && !change) {
    //     cout << "123" << endl;
    //    	Game::camera->removeImmediateChild(currentScene);
    //     currentScene = scene1;
    //     Game::camera->addChild(currentScene);
    //     change = !change;
    // }

    //for music - press1 and the music will play
	//user press 1 --> play music
	if ((pressedKeys.find(SDL_SCANCODE_1) != pressedKeys.end())) {
		cout<<"playing?"<<endl;
		mainMusic->playMusic();	
	} 
	//user press2 --> stop music
    if ((pressedKeys.find(SDL_SCANCODE_2) != pressedKeys.end())) {
		cout<<"pause playing"<<endl;
		mainMusic->pauseMusic();	
	}

	//changing position of camera
	if (Game::camera->position.x > currentScene->right) {
		if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
			Game::camera->position.x-=5;
		}
	}
	if (Game::camera->position.x < currentScene->left) {
		if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
			Game::camera->position.x+=5;
		}
	}	
	if (Game::camera->position.y > currentScene->bottom) {
		if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
			Game::camera->position.y-=5;
		}
	}	
	if (Game::camera->position.y < currentScene->top) {
		if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
			Game::camera->position.y+=5;
		}
	}


	//character moves separately from scene
	if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end()) {

		//currentScene->getCharacter()->prevPos.y = currentScene->getCharacter()->position.y;
		//currentScene->getCharacter()->position.y -=2;
	}
	if (pressedKeys.find(SDL_SCANCODE_S) != pressedKeys.end()) {
		//currentScene->getCharacter()->prevPos.y = currentScene->getCharacter()->position.y;
		//currentScene->getCharacter()->position.y +=2;
	}
	if (pressedKeys.find(SDL_SCANCODE_A) != pressedKeys.end()) {
		//currentScene->getCharacter()->facingRight = false;
		//currentScene->getCharacter()->prevPos.x = currentScene->getCharacter()->position.x;
		//currentScene->getCharacter()->position.x -=2;

			// currentScene->position.x+=2; //comment out to just move sprite
	}
	if (pressedKeys.find(SDL_SCANCODE_D) != pressedKeys.end()) {
		//currentScene->getCharacter()->facingRight = true;
		//currentScene->getCharacter()->prevPos.x = currentScene->getCharacter()->position.x;
		//currentScene->getCharacter()->position.x +=2; 

			// currentScene->position.x-=2; //comment out to just move sprite
	}
	//double jump
	if (pressedKeys.find(SDL_SCANCODE_Z)!=pressedKeys.end()){
		currentScene->getPlayer()->setState("double jump");//prevPos.y = currentScene->getCharacter()->position.y;
		//currentScene->getCharacter()->position.y +=2;
	}
	//ghost
	if (pressedKeys.find(SDL_SCANCODE_G)!=pressedKeys.end()){
		currentScene->getPlayer()->setState("ghost");//prevPos.y = currentScene->getCharacter()->position.y;
		//currentScene->getCharacter()->position.y +=2;
	}
	//sprint
	if (pressedKeys.find(SDL_SCANCODE_X)!=pressedKeys.end()){
		currentScene->getPlayer()->setState("sprint");//prevPos.y = currentScene->getCharacter()->position.y;
		//currentScene->getCharacter()->position.y +=2;
	}	
	//shield
	if (pressedKeys.find(SDL_SCANCODE_V)!=pressedKeys.end()){
		currentScene->getPlayer()->setState("shield");//prevPos.y = currentScene->getCharacter()->position.y;
		//currentScene->getCharacter()->position.y +=2;
	}
	//hover 
	if (pressedKeys.find(SDL_SCANCODE_B)!=pressedKeys.end()){
		currentScene->getPlayer()->setState("High jump");
	}

	/***************** UI COMPONENTS ******************/
	if ( controls->openMenu() && !change && !currentScene->getPlayer()->inBattle) {
		mainMenu->visible = true; 
		Tween* menuTween = new Tween(mainMenu);
		TweenableParams malpha;
		malpha.name = "alpha";
		menuTween->animate(malpha, 0, 255, 3); 
		tj->add(menuTween);
		change = !change;
	}
	else if (controls->openMenu() && change ) {
		mainMenu->visible = false; 
		Tween* menuTween = new Tween(mainMenu);
		TweenableParams malpha;
		malpha.name = "alpha";
		menuTween->animate(malpha, 255, 0, 3); 
		tj->add(menuTween);
		change = !change;
	}
	/* if (pressedKeys.find(SDL_SCANCODE_U) != pressedKeys.end() && !tchange) {
		tBox->visible = true; 
		Tween* textTween = new Tween(tBox);
		TweenableParams talpha;
		talpha.name = "alpha";
		textTween->animate(talpha, 0, 255, 3);
		tj->add(textTween);
		tchange = !tchange;
	}
	else if (pressedKeys.find(SDL_SCANCODE_U) != pressedKeys.end() && tchange) {
		tBox->visible = false; 
		Tween* textTween = new Tween(tBox);
		TweenableParams talpha;
		talpha.name = "alpha";
		textTween->animate(talpha, 255, 0, 3);
		tj->add(textTween);
		tchange = !tchange;
	}
	// To change text
	if (pressedKeys.find(SDL_SCANCODE_J) != pressedKeys.end()) {
		tBox->setText("Testing this out !"); 
	}	 */
	//updating camera position
    Game::camera->camera.x =  currentScene->position.x + currentScene->width/2 - 400;
	Game::camera->camera.y =  currentScene->position.y + currentScene->height/2 - 350;

	// cout << "Camera x " << Game::camera->position.x << endl; 
	// cout << "Camera y " << Game::camera->position.y << endl; 
	// cout << "Character x " << currentScene->getPlayer()->position.x << endl;
	// cout << "Character y " << currentScene->getPlayer()->position.y << endl;
	if( Game::camera->camera.x < 0){
		Game::camera->camera.x = 0;
	}
    if( Game::camera->camera.y < 0 ){
		Game::camera->camera.y = 0;
    }
	if (Game::camera->camera.x > Game::camera->camera.w){
		Game::camera->camera.x = Game::camera->camera.w;
	}
	if (Game::camera->camera.y > Game::camera->camera.h) {
		Game::camera->camera.y = Game::camera->camera.h;
	}
	// //Change scene 
	// if ((currentScene == scene1) && (currentScene->getCharacter()->position.y < 70)) {
	// 		cout << "exited room!" << endl;
	// 		eDispatcher->dispatchEvent(new Event(CHANGE, eDispatcher, currentScene->getCharacter(), 
	// 			scene2));
	// 		cout << "out of dispatcher" << endl;
	// 		Game::camera->removeImmediateChild(currentScene);
	// 		currentScene = sm->getCurrentScene();       
	// 		Game::camera->addChild(currentScene);
	// 		eDispatcher->addEventListener(sm, CHANGE);
	// }
	// else if ((currentScene->enemies.size() > 0) && (!fight) && (isCharInCoin(currentScene->getCharacter(), currentScene->getEnemy(0)))) {
	// 	cout << "inside fight!" << endl;
	// 	eDispatcher->dispatchEvent(new Event(FIGHT, eDispatcher, currentScene->getCharacter(),
	// 		currentScene->getEnemy(0), scene3));
	// 	Game::camera->removeImmediateChild(currentScene);
	// 	currentScene = sm->getCurrentScene();       
	// 	Game::camera->addChild(currentScene);
	// 	fight = true;
	// 	eDispatcher->addEventListener(sm, REVERT);
	// }
	// else if ((fight) && (isCharInCoin(currentScene->getCharacter(), currentScene->getEnemy(0)))) {
	// 		cout << "inside revert!" << endl;
	// 		eDispatcher->dispatchEvent(new Event(REVERT, eDispatcher));
	// 		cout << "out of revert dispatch" << endl;
	// 		Game::camera->removeImmediateChild(currentScene);
	// 		currentScene = sm->getCurrentScene();      
	// 		Game::camera->addChild(currentScene);
	// 		fight = false;
	// 		// eDispatcher->addEventListener(sm, CHANGE);
	// 		// eDispatcher->addEventListener(sm, FIGHT);
	// }
	// else if ((currentScene == scene2) && (currentScene->getCharacter()->position.y > 572)) {
	// 		cout << "exited mountain!" << endl;
	// 		// eDispatcher->dispatchEvent(new Event(REVERT, eDispatcher, currentScene->getCharacter(), 
	// 		//	scene1));
	// 		eDispatcher->dispatchEvent(new Event(REVERT, eDispatcher));
	// 		cout << "out of dispatcher" << endl;
	// 		Game::camera->removeImmediateChild(currentScene);
	// 		currentScene = sm->getCurrentScene();       
	// 		Game::camera->addChild(currentScene);
	// 		eDispatcher->addEventListener(sm, CHANGE);
	// }

	//sm->handleEvent(CHANGE);
	tj->nextFrame(); 
	
	// cout << "Char alpha " << currentScene->getCharacter()->alpha << endl;
	Game::update(pressedKeys, pressedButtons, movedAxis);
	collisionSystem->update();

	// currentScene->doCam = cam->camera;
}

void MyGame::draw(AffineTransform &at){
	Game::draw(at); 
	SDL_RenderSetViewport(Game::renderer, &Game::camera->camera);
}
