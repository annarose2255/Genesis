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

using namespace std;

MyGame::MyGame() : Game(800, 700) { //rendered space
	instance = this;
    scene1 = new Scene();
    // scene1->loadScene("./resources/scenes/character.json");
	scene1->loadTileMap("./resources/scenes/area 1 files/tsx files/Area 1 - Room 7.tmx");
	// scene2 = new Scene();
	// scene2->loadScene("./resources/scenes/solarsystem.json");
	// // scene2->loadTileMap("./resources/scenes/area 1 files/tsx files/Area 1 - Room 5.tmx", true);
	// scene3 = new Scene();
	// scene3->loadScene("./resources/scenes/fight1.json");
    change = true;
    currentScene = scene1;

    // UI Components
    hp = new HealthBar(0, 100, 0);

	Game::camera->addChild(currentScene);
	instance->addChild(hp);
	instance->addChild(Game::camera);

	hp->position = { 100, 100 };
    //Sound 
	mainMusic = new Sound();

	//Change Scene 
	sm = new SceneManager(currentScene->getCharacter(), currentScene);
	eDispatcher = EventDispatcher::getInstance();
	eDispatcher->addEventListener(sm, CHANGE);
	//QuestDemo
	// eDispatcher = new EventDispatcher();
	// // cout << "up to dispatcher" << endl;
	// coinlis = new CoinListener(scene1->getCharacter(), scene1->objects.at(0));
	// // cout << "we good" << endl;
	// myQuestManager = new QuestManager(scene1->objects.at(1));
	// eDispatcher->addEventListener(coinlis, PICKUP);
	// eDispatcher->addEventListener(myQuestManager, COLLECTED);

	//Tween
	tj = new TweenJuggler();
	Tween* charTween = new Tween(currentScene->getCharacter());
	TweenableParams chalpha;
	chalpha.name = "alpha";
	charTween->animate(chalpha, 0, 255, 3); 
	
	// TweenEvent te = new TweenEvent("enterChara", charTween); //handle events 
	//mimic coin demo
	tj->add(charTween);

}

MyGame::~MyGame(){
}


void MyGame::update(set<SDL_Scancode> pressedKeys, ControllerInput controllerInput){
    
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

	//changing position of scene
	if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
		Game::camera->position.x-=5;
	}
	if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
		Game::camera->position.x+=5;
	}
	//for prev hw
	//if (Game::camera->position.y-5 > 0) {
		if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
			Game::camera->position.y-=5;
		}	
	//}
	if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
		Game::camera->position.y+=5;
	}

	//character moves separately from scene
	if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end()) {
		currentScene->getCharacter()->position.y -=2;
	}
	if (pressedKeys.find(SDL_SCANCODE_S) != pressedKeys.end()) {
		currentScene->getCharacter()->position.y +=2;
	}
	if (pressedKeys.find(SDL_SCANCODE_A) != pressedKeys.end()) {
		currentScene->getCharacter()->facingRight = false;
		currentScene->getCharacter()->position.x -=2;
			// currentScene->position.x+=2; //comment out to just move sprite
	}
	if (pressedKeys.find(SDL_SCANCODE_D) != pressedKeys.end()) {
		currentScene->getCharacter()->facingRight = true;
		currentScene->getCharacter()->position.x +=2; 
			// currentScene->position.x-=2; //comment out to just move sprite
	}
	//updating camera position
    Game::camera->camera.x =  currentScene->position.x +  currentScene->width/2 - 400;
	Game::camera->camera.y =  currentScene->position.y +  currentScene->height/2 - 350;
	// cout << "Scene sx " << currentScene->scaleX << endl; 
	// cout << "Scene sy " << currentScene->scaleY << endl; 
	// cout << "Character x " << currentScene->getCharacter()->position.x << endl;
	// cout << "Character y " << currentScene->getCharacter()->position.y << endl;
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
	//Quest Demo stuff
	// if (currentScene->objects.size() > 0) {
	// 	// cout << "objects exist" << endl;
	// 	if (currentScene->objects.at(0)->visible && isCharInCoin(currentScene->getCharacter(), currentScene->objects.at(0))) {
	// 		Tween* coinTween = new Tween(currentScene->objects.at(0));
	// 		TweenableParams gx, gy, gsx, gsy, coinfade;
	// 		gx.name = "position.x";
	// 		gy.name = "position.y";
	// 		gsx.name = "scaleX";
	// 		gsy.name = "scaleY";
	// 		coinfade.name = "alpha";
	// 		cout << "MyGame coin pos x " << currentScene->objects.at(0)->position.x << endl;
	// 		cout << "MyGame coin pos y " << currentScene->objects.at(0)->position.y << endl;
	// 		coinTween->animate(gx, currentScene->objects.at(0)->position.x, 600, 5);
	// 		coinTween->animate(gy, currentScene->objects.at(0)->position.y, 300, 5); 
	// 		coinTween->animate(gsx, currentScene->objects.at(0)->scaleX, 2, 5);
	// 		coinTween->animate(gsy, currentScene->objects.at(0)->scaleY, 2, 5);
	// 		coinTween->animate(coinfade, 255, 0, 5);
	// 		//need a TweenEvent Listener here to start the coin fade animation
	// 		//TweenEvent te = new TweenEvent(COLLECTED, coinTween)
	// 		//eDispatcher->addNewListener(te, COLLECTED);
	// 		//once the coin is 2x bigger then begin the fade transition
	// 		// coinTween->animate(coinfade, 255, 0, 5); 
	// 		tj->add(coinTween);
	// 		// eDispatcher->removeEventListener(coinlis, PICKUP);
	// 		// eDispatcher->dispatchEvent(new Event(PICKUP, eDispatcher));
	// 		// currentScene->addChild(questComplete);
    // 	}
	// 	if (!currentScene->objects.at(0)->visible && isOngoing)
	// 	{
	// 		// cout << "collected event" << endl;
	// 		isOngoing = false;
	// 		// eDispatcher->dispatchEvent(new Event(COLLECTED, eDispatcher));
	// 	}
	// }
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

