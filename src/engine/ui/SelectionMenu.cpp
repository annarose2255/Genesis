#include "SelectionMenu.h"
#include "DisplayObject.h"
#include "Game.h"
#include "MenuItem.h"
#include <iostream>

using namespace std;

SelectionMenu::SelectionMenu() : Sprite() {
	this->id = "SelectionMenu";

	this->width = 800;
	this->height = 100;
	this->visible = false;

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
	}
}

void SelectionMenu::goBack() {
	if(prevItem != NULL) {
		this->visible = false;
		prevItem->prevMenu->visible = true;
	}
}

void SelectionMenu::update(set<SDL_Scancode> pressedKeys) {
	// Only accept inputs if visible
	if(this->visible) {
		if (pressedKeys.size() == 1){
			for(SDL_Scancode key : pressedKeys) {
				switch (key) {
					case SDL_SCANCODE_RETURN:
						this->selectItem(selectInd);
						break;
					case SDL_SCANCODE_BACKSPACE:
						this->goBack();
						break;
					case SDL_SCANCODE_N:
						if (selectInd != 0) {
							selectInd -= 1;
						}
						break;
					case SDL_SCANCODE_M:
						if (selectInd != menuItems.size()-1) {
							selectInd +=1;
						}
						break;
				}
			}
		}
	}
}

void SelectionMenu::draw(AffineTransform &at) {
	if(this->visible) {
		Sprite::draw(at);
		cout << "uhh" << endl;

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
			SDL_RenderDrawLine(Game::renderer, this->position.x+itemPos.x, this->position.y+itemPos.y+itemH+30, this->position.x+itemPos.x+itemW, this->position.y+itemPos.y+itemH+3);
		}

		// Reset to black
		SDL_SetRenderDrawBlendMode(Game::renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, this->alpha);

	}

}