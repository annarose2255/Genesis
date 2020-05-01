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
		MyGame::currentScene->selectitem = true;
	} else if (selItem->itemAction != NULL) {
		selItem->action(MyGame::eDispatcher); // This game's dispatcher
		MyGame::currentScene->selectitem = true;
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
	//cout<<"enemy turn3: "<<enemyTurn<<endl;
	//selectedaitem = false;
	if(MyGame::controls->select() && MyGame::currentScene->dead){
		MyGame::currentScene->dead = false;
		MyGame::eDispatcher->dispatchEvent(new Event(REVERT, MyGame::eDispatcher, MyGame::currentScene->getPlayer(), 
						MyGame::currentScene->getEnemy()));
	}
	if(MyGame::controls->select() && enemyTurn == true && !MyGame::currentScene->dead){ //end of player turn textbox
	cout<<"enemy turn2: "<<MyGame::currentScene->numChildren()<<endl;
		if (MyGame::currentScene->numChildren() == 2 ){
			MyGame::currentScene->removeChild(1);
			//MyGame::actionMenu->visible = true;
			//MyGame::eDispatcher->
			MyGame::eDispatcher->dispatchEvent(new Event(ENEMYTURN, MyGame::eDispatcher, MyGame::currentScene->getPlayer(), 
					MyGame::currentScene->getEnemy()));
					betweenturns = true;
			
			//cout<<"enemy turn3: "<<enemyTurn<<endl;
		}
	}
		//if (this->getItem(0)->getAction() == NULL){
	//cout<<"between: "<<betweenturns<<endl;
	if (MyGame::controls->select() && !decideFate && betweenturns && !MyGame::currentScene->dead){ //end of enemy turn textbox
		cout<<"enemy turn: "<<endl;
		MyGame::currentScene->removeChild(1);
		//cout<<"C"<<endl;
		MyGame::currentScene->selectitem = false;
		MyGame::actionMenu->visible = true;
		//cout << "inside enemy" << endl;
		if (MyGame::actionMenu->getItem(0)->getAction() == NULL){
			MyGame::actionMenu->getItem(0)->setAction(new Event(ATTACK, MyGame::eDispatcher, MyGame::currentScene->getPlayer(), 
				MyGame::currentScene->getEnemy()));
		}
		/* if (this->getItem(1)->getAction() == NULL){
			this->getItem(1)->setAction(new Event(DEFEND, MyGame::eDispatcher, MyGame::currentScene->getPlayer(), 
				MyGame::currentScene->getEnemy()));
		} */
		/* if (this->getItem(2)->nextMenu->getItem(0)->visible && this->getItem(2)->nextMenu->getItem(0)->getAction() == NULL){
			this->getItem(2)->nextMenu->getItem(0)->setAction(new Event(GHOST, MyGame::eDispatcher, MyGame::currentScene->getPlayer(), 
				MyGame::currentScene->getEnemy()));
		}
		if (this->getItem(2)->nextMenu->getItem(3)->visible && this->getItem(2)->nextMenu->getItem(3)->getAction() == NULL){
			this->getItem(2)->nextMenu->getItem(3)->setAction(new Event(STRENGTHCOMBAT, MyGame::eDispatcher, MyGame::currentScene->getPlayer(), 
				MyGame::currentScene->getEnemy()));
		} */
		enemyTurn = false;
		betweenturns = false;
	}
	if (decideFate && MyGame::controls->select() && !MyGame::currentScene->dead) { //defeated enemy
		cout << "inside decide fate" << endl;
		cout<<"child : "<<MyGame::currentScene->numChildren()<<endl;
		if (MyGame::currentScene->numChildren() == 2 ){
			cout<<"num child 3"<<endl;
			//MyGame::currentScene->removeChild(2);
			MyGame::currentScene->selectitem = false;
			MyGame::currentScene->removeChild(1);
			MyGame::actionMenu->visible = false;
			MyGame::eDispatcher->dispatchEvent(new Event(DECIDEFATE, MyGame::eDispatcher, MyGame::currentScene->getPlayer(),
				MyGame::currentScene->getEnemy()));
		}
	}
	//MyGame::currentScene->selectitem = false;
	counter_for_pressing++;
	if(this->visible) {
		if (MyGame::controls->select()){
			if(!enemyTurn){
				//if (Game::frameCounter%6 == 0) {
				if (this == MyGame::abilities){
					cout<<"ability"<<endl;
					if (Game::frameCounter%5 == 0) {
						cout<<"frame2: "<<Game::frameCounter<<endl;
						cout<<"select2: "<<selectInd<<endl;
						selectItem(selectInd);
					}
				}
				else{
					cout<<"frame: "<<Game::frameCounter<<endl;
					cout<<"select: "<<selectInd<<endl;
					selectItem(selectInd);
				}
					//if (MyGame::currentScene->selectitem == false){

					//}
					/* if (MyGame::abilities->visible && MyGame::abilities->numChildren() < 3){
						cout<<"frame2: "<<Game::frameCounter<<endl;
						cout<<"select2: "<<selectInd<<endl;
						selectItem(selectInd);
					} */
				//}
			}
		}
		else if (MyGame::controls->back()){
			this->goBack();
			MyGame::currentScene->selectitem = false;
		}
		else if (MyGame::controls->holdRight()){
			if (selectInd != menuItems.size()-1 && Game::frameCounter%4 == 0) {
				selectInd +=1;
				MyGame::currentScene->selectitem = false;
			}
			
		}
		else if (MyGame::controls->holdLeft()){
			if (selectInd != 0 && Game::frameCounter%4 == 0) {
				selectInd -= 1;
				MyGame::currentScene->selectitem = false;
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