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

using namespace std;

EventDispatcher* MyGame::eDispatcher = EventDispatcher::getInstance();
Scene* MyGame::currentScene = new Scene();
TweenJuggler* MyGame::tj = new TweenJuggler();
CollisionSystem* MyGame::collisionSystem = new CollisionSystem();

MyGame::MyGame() : Game(800, 700) { //rendered space
	instance = this;
	eDispatcher->addEventListener(collisionSystem, DO_ADDED_EVENT);
    scene1 = new Scene();
    // scene1->loadScene("./resources/scenes/character.json");
	scene1->loadTileMap("./resources/scenes/area1files/Area1Room7.json");
	// scene1->loadScene("./resources/scenes/Room7.json");
	// scene1->loadScene("./resources/scenes/char.json");
	scene1->loadScene("./resources/scenes/ghostchar.json");
	//test playable char
	// AnimatedSprite* chara = new AnimatedSprite("chara"); 
	// chara->addSSAnimation("./resources/ghostchar/idle.png", "./resources/ghostchar/idle.xml");
	// chara->play("Idle");
    // chara->position = {70, 200};
	// Game::camera->addChild(chara);
	
    change = true;
    currentScene = scene1;

    // UI Components
    hp = new HealthBar(0, 100, 0);
    tBox = new TextBox();
    tBox->setText("Hello World !");

    mainMenu = new SelectionMenu();
    MenuItem* items = new MenuItem("Items", 0, 0);
    MenuItem* save = new MenuItem("Save", 250, 0);
    MenuItem* settings = new MenuItem("Settings", 500, 0);
    mainMenu->addItem(items);
    mainMenu->addItem(save);
    mainMenu->addItem(settings);
    mainMenu->position.x = 200;
    mainMenu->position.y = 300;
    mainMenu->visible = false;


	Game::camera->addChild(currentScene);
	instance->addChild(hp);
	instance->addChild(tBox);
	instance->addChild(mainMenu);
	instance->addChild(Game::camera);

	hp->position = { 100, 100 };
    //Sound 
	mainMusic = new Sound();
	//Change Scene 
	sm = new SceneManager(currentScene->getCharacter(), currentScene);
	eDispatcher = EventDispatcher::getInstance();
	eDispatcher->addEventListener(sm, CHANGE);
	//Collision Detection 
	collisionSystem->watchForCollisions("character", "platform"); 
	// collisionSystem->watchForCollisions("character", "enemy");
	//Tween
	// tj = new TweenJuggler();
	Tween* charTween = new Tween(currentScene->getCharacter());
	TweenableParams chalpha;
	chalpha.name = "alpha";
	charTween->animate(chalpha, 0, 255, 3); 
	
	// TweenEvent te = new TweenEvent("enterChara", charTween); //handle events 
	//mimic coin demo
	tj->add(charTween);



}

MyGame::~MyGame(){
	delete currentScene; 
	delete tj; 
	delete eDispatcher;
}


void MyGame::update(set<SDL_Scancode> pressedKeys, ControllerInput controllerInput){
    mainMenu->update(pressedKeys);
    if(pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end() && change) {
        cout << "abc" << endl;
        Game::camera->removeImmediateChild(currentScene);
        cout << instance->children.size() << endl;
        currentScene = scene2;
        Game::camera->addChild(currentScene);
        change = !change;
    }
    else if(pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end() && !change) {
        cout << "123" << endl;
       	Game::camera->removeImmediateChild(currentScene);
        currentScene = scene1;
        Game::camera->addChild(currentScene);
        change = !change;
    }
	if ((pressedKeys.find(SDL_SCANCODE_Z) != pressedKeys.end())) {
		currentScene->scaleX+=0.01; 
		currentScene->scaleY+=0.01;	
	}
	if (currentScene->scaleX > 1 && currentScene->scaleY > 1) {
		if ((pressedKeys.find(SDL_SCANCODE_X) != pressedKeys.end())) {
			currentScene->scaleY-=0.01;
			currentScene->scaleX-=0.01;
		}
	}

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
		currentScene->getCharacter()->prevPos.y = currentScene->getCharacter()->position.y;
		currentScene->getCharacter()->position.y -=2;
	}
	if (pressedKeys.find(SDL_SCANCODE_S) != pressedKeys.end()) {
		currentScene->getCharacter()->prevPos.y = currentScene->getCharacter()->position.y;
		currentScene->getCharacter()->position.y +=2;
	}
	if (pressedKeys.find(SDL_SCANCODE_A) != pressedKeys.end()) {
		currentScene->getCharacter()->facingRight = false;
		currentScene->getCharacter()->prevPos.x = currentScene->getCharacter()->position.x;
		currentScene->getCharacter()->position.x -=2;
			// currentScene->position.x+=2; //comment out to just move sprite
	}
	if (pressedKeys.find(SDL_SCANCODE_D) != pressedKeys.end()) {
		currentScene->getCharacter()->facingRight = true;
		currentScene->getCharacter()->prevPos.x = currentScene->getCharacter()->position.x;
		currentScene->getCharacter()->position.x +=2; 
			// currentScene->position.x-=2; //comment out to just move sprite
	}
	if (pressedKeys.find(SDL_SCANCODE_Y) != pressedKeys.end()) {
		mainMenu->visible = true; 
	}		
	//updating camera position
    Game::camera->camera.x =  currentScene->position.x +  currentScene->width/2 - 400;
	Game::camera->camera.y =  currentScene->position.y +  currentScene->height/2 - 350;
	// cout << "Camera x " << Game::camera->position.x << endl; 
	// cout << "Camera y " << Game::camera->position.y << endl; 
	cout << "Character x " << currentScene->getCharacter()->position.x << endl;
	cout << "Character y " << currentScene->getCharacter()->position.y << endl;
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
	collisionSystem->update();
	// cout << "Char alpha " << currentScene->getCharacter()->alpha << endl;
	Game::update(pressedKeys, controllerInput);
	// currentScene->doCam = cam->camera;
}

void MyGame::draw(AffineTransform &at){
	Game::draw(at); 
	SDL_RenderSetViewport(Game::renderer, &Game::camera->camera);
}

bool MyGame::isCharInCoin(DisplayObject* chara, DisplayObject* cn) {
    SDL_Point* charPos, charTemp;
    SDL_Rect* cnRect, cnTemp;
    charTemp = {chara->position.x + chara->pivot.x, chara->position.y + chara->pivot.y};
    charPos = &charTemp; 
    cnTemp = {cn->position.x, cn->position.y, cn->width, cn->height};
    cnRect = &cnTemp;
    return SDL_PointInRect(charPos, cnRect);
}

