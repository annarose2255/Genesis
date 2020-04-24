#include "SelectionMenu.h"
#include "DisplayObject.h"
#include "Game.h"
#include "MyGame.h"
#include "MenuItem.h"
#include <iostream>

using namespace std;

SelectionMenu::SelectionMenu() : Sprite() {
	this->id = "SelectionMenu";

	this->width = 799;
	this->height = 99;
	this->visible = false;
	this->isUI = true;
	selectInd = 0;
	prevItem = NULL;

}

SelectionMenu::~SelectionMenu() {
}

// addItem() automatically adds item as a child
void SelectionMenu::addItem(MenuItem* item) {
	this->addChild(item);
	menuItems.push_back(item);
	item->prevMenu = this;
}

void SelectionMenu::selectItem(int ind) {
	MenuItem* selItem = menuItems[ind];
	if(selItem->nextMenu != NULL) {
		this->visible = false;
		selItem->nextMenu->prevItem = selItem;
		selItem->nextMenu->visible = true;
	} else if (selItem->itemAction != NULL) {
		selItem->action(MyGame::eDispatcher); // This game's dispatcher
		cout << "DISPATCH ACTION" << endl;
	}
}

void SelectionMenu::goBack() {
	if(prevItem != NULL) {
		this->visible = false;
		prevItem->prevMenu->visible = true;
	}
}
MenuItem* SelectionMenu::getItem(int index) {
	return menuItems[index];
}
void SelectionMenu::update(set<SDL_Scancode> pressedKeys, set<SDL_GameControllerButton> pressedButtons, set<pair<SDL_GameControllerAxis, float>> movedAxis) {
	// Only accept inputs if visible
	//counter_for_pressing++;
	if(pressedKeys.find(SDL_SCANCODE_SPACE) != pressedKeys.end() && enemyTurn == false){ //end of player turn textbox
		if (MyGame::currentScene->numChildren() == 2 ){
			MyGame::currentScene->removeChild(1);
			//MyGame::actionMenu->visible = true;
			//MyGame::eDispatcher->
			MyGame::eDispatcher->dispatchEvent(new Event(ENEMYTURN, MyGame::eDispatcher, MyGame::currentScene->getPlayer(), 
					MyGame::currentScene->getEnemy()));
			enemyTurn = true;
		}
	}
		//if (this->getItem(0)->getAction() == NULL){
	if (pressedKeys.find(SDL_SCANCODE_C) != pressedKeys.end() && !decideFate){ //end of enemy turn textbox
		MyGame::currentScene->removeChild(1);
		MyGame::actionMenu->visible = true;
		cout << "inside enemy" << endl;
		if (this->getItem(0)->getAction() == NULL){
			this->getItem(0)->setAction(new Event(ATTACK, MyGame::eDispatcher, MyGame::currentScene->getPlayer(), 
				MyGame::currentScene->getEnemy()));
		}
		enemyTurn = false;
	}
	if (decideFate && pressedKeys.find(SDL_SCANCODE_TAB) != pressedKeys.end()) { //defeated enemy
		cout << "inside decide fate" << endl;
		cout<<"child : "<<MyGame::currentScene->numChildren()<<endl;
		if (MyGame::currentScene->numChildren() == 2 ){
			cout<<"num child 3"<<endl;
			//MyGame::currentScene->removeChild(2);
			MyGame::currentScene->removeChild(1);
			MyGame::actionMenu->visible = false;
			MyGame::eDispatcher->dispatchEvent(new Event(DECIDEFATE, MyGame::eDispatcher, MyGame::currentScene->getPlayer(),
				MyGame::currentScene->getEnemy()));
		}
	}
	if(this->visible) {
		for(SDL_Scancode key : pressedKeys) {
			switch (key) {
				case SDL_SCANCODE_RETURN:
					// cout<<"selected item: "<<counter_for_pressing<<endl;
					// counter_for_pressing++;
					// if (counter_for_pressing >= 1){
					// 	if (counter_for_pressing == 1){
					// 		this->selectItem(selectInd);
					// 	}
					// 	else if (counter_for_pressing == 4) {
					// 		counter_for_pressing = 0;
					// 	}
					// 	else{
					// 		break;
					// 	}
					if(!enemyTurn){
						this->selectItem(selectInd);
					}
					break;
				case SDL_SCANCODE_BACKSPACE:
					this->goBack();
					break;
				case SDL_SCANCODE_N:
					if (selectInd != 0 && Game::frameCounter%12 == 0) {
						selectInd -= 1;
					}
					break;
				case SDL_SCANCODE_M:
					if (selectInd != menuItems.size()-1 && Game::frameCounter%12 == 0) {
						selectInd +=1;
					}
					break;
			}
		}
	}
	Sprite::update(pressedKeys, pressedButtons, movedAxis);
}

void SelectionMenu::draw(AffineTransform &at) {
	if(this->visible) {
		Sprite::draw(at);

		SDL_SetRenderDrawBlendMode(Game::renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, this->alpha);
		
		// Draw a white border around the Selection Menu
		SDL_RenderDrawLine(Game::renderer, this->position.x, this->position.y, this->position.x + this->width, this->position.y);
		SDL_RenderDrawLine(Game::renderer, this->position.x+this->width, this->position.y, this->position.x + this->width, this->position.y+this->height);
		SDL_RenderDrawLine(Game::renderer, this->position.x+this->width, this->position.y+this->height, this->position.x, this->position.y+this->height);
		SDL_RenderDrawLine(Game::renderer, this->position.x, this->position.y, this->position.x, this->position.y+this->height);

		// Draw blinking white line under Selected
		if (Game::frameCounter%60 > 0 && Game::frameCounter%60 < 31) {
			SDL_Point itemPos = menuItems[selectInd]->position;
			int itemW = menuItems[selectInd]->width;
			int itemH = menuItems[selectInd]->height;
			SDL_RenderDrawLine(Game::renderer, this->position.x+itemPos.x, this->position.y+itemPos.y+itemH+5, this->position.x+itemPos.x+itemW, this->position.y+itemPos.y+itemH+5);
		}

	}

}