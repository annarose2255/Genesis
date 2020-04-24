#include "MenuItem.h"
#include "DisplayObject.h"
#include "Game.h"
#include <iostream>
#include "SelectionMenu.h"

using namespace std;

MenuItem::MenuItem(string name, int posX, int posY) : TextBox() {

	this->id = "MenuItem";

	this->position.x = posX;
	this->position.y = posY;
	this->isUI = true;
	this->width = 200;
	this->height = 40;

	this->setText(name);

	this->nextMenu = NULL;

}

MenuItem::MenuItem(string name, int posX, int posY, Event* e) : TextBox() {
	this->id = "MenuItem";

	this->position.x = posX;
	this->position.y = posY;
	this->isUI = true;
	this->width = 200;
	this->height = 40;

	this->setText(name);
	this->setAction(e);

	this->nextMenu = NULL;
}

MenuItem::~MenuItem() {
}

void MenuItem::update(set<SDL_Scancode> pressedKeys, set<SDL_GameControllerButton> pressedButtons, set<pair<SDL_GameControllerAxis, float>> movedAxis) {
	TextBox::update(pressedKeys, pressedButtons, movedAxis);
}

void MenuItem::draw(AffineTransform &at) {
	Sprite::draw(at);
}
Event* MenuItem::getAction(){
	return this->itemAction;
}
void MenuItem::setAction(Event* e) {
	this->itemAction = e;
}

void MenuItem::action(EventDispatcher* ed) {
	ed->dispatchEvent(itemAction);
}