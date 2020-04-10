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

	selectInd = 0;

}

SelectionMenu::~SelectionMenu() {
}

// addItem() automatically adds item as a child
void SelectionMenu::addItem(MenuItem* item) {
	this->addChild(item);
	item->prevMenu = this;
}

void SelectionMenu::selectItem(int ind) {
	MenuItem* selItem = menuItems[ind];
	if(selItem != NULL) {
		this->visible = false;
		selItem->nextMenu->visible = true;
	}
}

void SelectionMenu::update(set<SDL_Scancode> pressedKeys) {
	// Only accept inputs if visible
	if(this->visible) {
		for(SDL_Scancode key : pressedKeys) {
			switch (key) {
				case SDL_SCANCODE_RETURN:
					this->selectItem(selectInd);
					break;
				case SDL_SCANCODE_LEFT:
					if (selectInd != 0) {
						selectInd -= 1;
					}
					break;
				case SDL_SCANCODE_RIGHT:
					if (selectInd != menuItems.size()-1) {
						selectInd +=1;
					}
					break;
			}
		}
	}
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
		if (Game::frameCounter%60 == 0) {
			SDL_Point itemPos = menuItems[selectInd]->position;
			int itemW = menuItems[selectInd]->width;
			int itemH = menuItems[selectInd]->height;
			SDL_RenderDrawLine(Game::renderer, itemPos.x, itemPos.y+itemH, itemPos.x+itemW, itemPos.y+itemH);
		}

	}

}