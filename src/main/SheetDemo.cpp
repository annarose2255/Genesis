#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Sprite.h"
#include "SheetDemo.h"
#include "QuestManager.h"

using namespace std;

SheetDemo::SheetDemo() : Game(1200, 1000) {
	instance = this;

	allSprites = new DisplayObjectContainer();
	// move that point to the middle
	allSprites->position = {600, 500};
	instance->addChild(allSprites);

	coin = new AnimatedSprite("coin", "./resources/quest/Gold.png", "./resources/quest/Gold.xml");
	questComplete = new DisplayObjectContainer("quest complete", "./resources/quest/questComplete.png");
	questComplete->visible = false;
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
    eDispatcher = EventDispatcher::getInstance();
	coinlis = new CoinListener(character, coin);
	myQuestManager = new QuestManager(questComplete);
	eDispatcher->addEventListener(coinlis, PICKUP);
	eDispatcher->addEventListener(myQuestManager, COLLECTED);
    isWalking = false;
    isJumping = false;
    left = false;
}

SheetDemo::~SheetDemo(){
}


void SheetDemo::update(set<SDL_Scancode> pressedKeys, set<SDL_GameControllerButton> pressedButtons, set<pair<SDL_GameControllerAxis, float>> movedAxis){


    if ( (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) || 
		 (pressedButtons.find(SDL_CONTROLLER_BUTTON_B) != pressedButtons.end()) ||
		 (pressedButtons.find(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) != pressedButtons.end()) ) {
		//cout << "RIGHT" << endl;
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
	if ( (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) || 
		 (pressedButtons.find(SDL_CONTROLLER_BUTTON_X) != pressedButtons.end()) ||
		 (pressedButtons.find(SDL_CONTROLLER_BUTTON_DPAD_LEFT) != pressedButtons.end()) ) {
		//cout << "LEFT" << endl;
		// cout << "printing X" << endl;
		// cout << SDL_CONTROLLER_BUTTON_X << endl;
		character->position.x -= 3;
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
	if ( (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) || 
		 (pressedButtons.find(SDL_CONTROLLER_BUTTON_A) != pressedButtons.end()) ||
		 (pressedButtons.find(SDL_CONTROLLER_BUTTON_DPAD_DOWN) != pressedButtons.end()) ) {
		//cout << "DONW" << endl;
		character->position.y += 3;
		//eDispatcher->dispatchEvent(new Event(PICKUP, eDispatcher));
        if (!isJumping){
            character->play("Jump");
            isJumping = true;
        }
	}
	if ( (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) || 
		 (pressedButtons.find(SDL_CONTROLLER_BUTTON_Y) != pressedButtons.end()) ||
		 (pressedButtons.find(SDL_CONTROLLER_BUTTON_DPAD_UP) != pressedButtons.end()) ) {
		// cout << "printing Y" << endl;
		// cout << SDL_CONTROLLER_BUTTON_Y << endl;
			 
		//cout << "UP" << endl;
		character->position.y -= 3;
        if (!isJumping){
            character->play("Jump");
            isJumping = true;
        }
	}
	if (pressedButtons.find(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) != pressedButtons.end()){
		character->rotation += 0.1;
	}
	if (pressedButtons.find(SDL_CONTROLLER_BUTTON_LEFTSHOULDER) != pressedButtons.end()){
		character->rotation -= 0.1;
	}
	if (pressedButtons.find(SDL_CONTROLLER_BUTTON_START) != pressedButtons.end()){
		controllerManager->rumbleController(0.7, 300);
	}

	// axis logic
	for (auto axis = movedAxis.begin(); axis != movedAxis.end(); axis++){
		if (axis->first == SDL_CONTROLLER_AXIS_TRIGGERLEFT){
			if (axis->second == 1){
				character->scaleX -= 0.1;
				character->scaleY -= 0.1;
			}
		}
		if (axis->first == SDL_CONTROLLER_AXIS_TRIGGERRIGHT){
			if (axis->second == 1){
				character->scaleX += 0.1;
				character->scaleY += 0.1;
			}
		}
		if (axis->first == SDL_CONTROLLER_AXIS_LEFTX){
			cout << axis->second << endl;
			if (axis->second > 0.5){
				character->position.x += 3;
			}
			if (axis->second < -0.5){
				character->position.x -= 3;
			}
		}
		if (axis->first == SDL_CONTROLLER_AXIS_LEFTY){
			cout << axis->second << endl;
			if (axis->second > 0.5){
				character->position.y += 3;
			}
			if (axis->second < -0.5){
				character->position.y -= 3;
			}
		}
	}

    if (coin->visible && isCharInCoin(character, coin)) { 
        eDispatcher->dispatchEvent(new Event(PICKUP, EventDispatcher::getInstance()));
        allSprites->removeImmediateChild(coin);
    }
	if (!coin->visible && isOngoing)
	{
		cout << "collected event" << endl;
		isOngoing = false;
        eDispatcher->dispatchEvent(new Event(COLLECTED, EventDispatcher::getInstance()));
	}
	Game::update(pressedKeys, pressedButtons, movedAxis);
}

void SheetDemo::draw(AffineTransform &at){
	Game::draw(at);
}

bool SheetDemo::isCharInCoin(DisplayObject* chara, DisplayObject* cn) {
    SDL_Point* charPos, charTemp;
    SDL_Rect* cnRect, cnTemp;
    charTemp = {chara->position.x + chara->pivot.x, chara->position.y + chara->pivot.y};
    charPos = &charTemp;
    cnTemp = {cn->position.x, cn->position.y, cn->width, cn->height};
    cnRect = &cnTemp;
    return SDL_PointInRect(charPos, cnRect);
}

