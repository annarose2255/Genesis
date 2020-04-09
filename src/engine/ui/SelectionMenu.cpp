#include "SelectionMenu.h"
#include "DisplayObject.h"
#include "Game.h"
#include <iostream>

using namespace std;

SelectionMenu::SelectionMenu() : Sprite() {
	this->id = "SelectionMenu";

	this->width = 800;
	this->height = 100;

}

SelectionMenu::~SelectionMenu() {
}

void SelectionMenu::addItem(string item) {

}

string SelectionMenu::selectItem(string item) {

	
}

void SelectionMenu::update(set<SDL_Scancode> pressedKeys) {

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


	}

}