#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Sprite.h"
#include "QuestDemo.h"
#include "QuestManager.h"

using namespace std;

QuestDemo::QuestDemo() : Game(1200, 1000) {
	instance = this;

	allSprites = new DisplayObjectContainer();
	// move that point to the middle
	allSprites->position = {600, 500};
	instance->addChild(allSprites);

	coin = new AnimatedSprite("coin");
	questComplete = new DisplayObjectContainer("quest complete", "./resources/quest/questComplete.png");
	questComplete->visible = false;
	coin->addAnimation("./resources/quest/", "Gold", 9, 4, true);
	coin->play("Gold");
	// cout << sun->getWidth() << sun->getHeight();
    coin->position = {0, 0};
	coin->width = coin->height = 100;
	coin->pivot = {50, 50};
	allSprites->addChild(coin);
	allSprites->addChild(questComplete);

    character = new AnimatedSprite("character");
    character->addAnimation("./resources/character/", "Walk", 20, 1, true);
    character->addAnimation("./resources/character/", "Run", 20, 1, true);
    character->addAnimation("./resources/character/", "Idle", 16, 1, true);
    character->addAnimation("./resources/character/", "Jump", 30, 1, false);
    character->addAnimation("./resources/character/", "Dead", 30, 1, false);

    character->play("Idle");
    allSprites->addChild(character);
    character->position = {-500, 200};
	character->pivot = {character->width/2, character->height/2};
    eDispatcher = new EventDispatcher();
	coinlis = new CoinListener(character, coin);
	myQuestManager = new QuestManager(questComplete);
	eDispatcher->addEventListener(coinlis, PICKUP);
	eDispatcher->addEventListener(myQuestManager, COLLECTED);
    isWalking = false;
    isJumping = false;
    left = false;
}

QuestDemo::~QuestDemo(){
}


void QuestDemo::update(set<SDL_Scancode> pressedKeys, ControllerInput controllerInput){
    // character->play("Idle");
    if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
		character->position.x += 3;
		//eDispatcher->dispatchEvent(new Event(PICKUP, eDispatcher));
        if (left){
            // character->scaleY = -1 * character->scaleX;
            left = false;
        }
        if (!isWalking){
            character->play("Walk");
            isWalking = true;
        }
	} else {
        if (!left && isWalking){
            character->play("Idle");
            isWalking = false;
        }
    }
	if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
		character->position.x -= 3;
		//eDispatcher->dispatchEvent(new Event(PICKUP, eDispatcher));
        if (!isWalking){
            // character->scaleX = -1 * character->scaleX;
            // character->scaleY = -1;
        }
        if (!left){
            // character->scaleY = -1 * character->scaleX;
            left = true;
        }
        if (!isWalking){
            character->play("Walk");
            isWalking = true;
        }

	} else {
        if (left && isWalking){
            character->play("Idle");
            isWalking = false;
        }
    }
	if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
		character->position.y += 3;
		//eDispatcher->dispatchEvent(new Event(PICKUP, eDispatcher));
        if (!isJumping){
            character->play("Jump");
            isJumping = true;
        }
	}
	if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
		character->position.y -= 3;
		//eDispatcher->dispatchEvent(new Event(PICKUP, eDispatcher));
        if (!isJumping){
            character->play("Jump");
            isJumping = true;
        }
	}
    if (coin->visible && isCharInCoin(character, coin)) { 
        eDispatcher->dispatchEvent(new Event(PICKUP, eDispatcher));
        allSprites->removeImmediateChild(coin);
    }
	if (!coin->visible && isOngoing)
	{
		cout << "collected event" << endl;
		isOngoing = false;
        eDispatcher->dispatchEvent(new Event(COLLECTED, eDispatcher));
	}
	// if (pressedKeys.find(SDL_SCANCODE_A) != pressedKeys.end()) {
	// 	// sun->rotation += 0.01;
	// 	p1container->rotation += 0.05;
	// 	p2container->rotation += 0.03;
	// 	planet1->rotation += 0.1;
	// 	p1container->position.x = 100*sin(p1container->rotation);
	// 	p2container->position.x = 100*sin(p2container->rotation);
	// }
	// if (pressedKeys.find(SDL_SCANCODE_S) != pressedKeys.end()) {
	// 	// sun->rotation -= 0.01;
	// 	p1container->rotation -= 0.05;
	// 	p2container->rotation -= 0.03;
	// 	planet1->rotation -= 0.1;
	// 	p1container->position.x = 100*sin(p1container->rotation);
	// 	p2container->position.x = 100*sin(p2container->rotation);
	// }
	// if (pressedKeys.find(SDL_SCANCODE_Q) != pressedKeys.end()) {
	// 	allSprites->scaleX *= 1.05;
	// 	allSprites->scaleY *= 1.05;
	// }
	// if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end()) {
	// 	allSprites->scaleX *= 1/1.05;
	// 	allSprites->scaleY *= 1/1.05;
	// }
	// if (pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end()) {
	// 	sun->play("Sun");
	// }
	// if (pressedKeys.find(SDL_SCANCODE_L) != pressedKeys.end()) {
	// 	sun->stop();
	// }
	Game::update(pressedKeys, controllerInput);
}

void QuestDemo::draw(AffineTransform &at){
	Game::draw(at);
}

bool QuestDemo::isCharInCoin(DisplayObject* chara, DisplayObject* cn) {
    SDL_Point* charPos, charTemp;
    SDL_Rect* cnRect, cnTemp;
    charTemp = {chara->position.x + chara->pivot.x, chara->position.y + chara->pivot.y};
    charPos = &charTemp;
    cnTemp = {cn->position.x, cn->position.y, cn->width, cn->height};
    cnRect = &cnTemp;
    return SDL_PointInRect(charPos, cnRect);
}

