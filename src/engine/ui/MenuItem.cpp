#include "MenuItem.h"
#include "DisplayObject.h"
#include "Game.h"
#include <iostream>
#include "SelectionMenu.h"

using namespace std;

MenuItem::MenuItem(int posX, int posY) : TextBox() {

	this->id = "MenuItem";

	this->position.x = posX;
	this->position.y = posY;

	this->width = 200;
	this->height = 40;

}

MenuItem::~MenuItem() {
}

void MenuItem::update(set<SDL_Scancode> pressedKeys) {

}

void MenuItem::draw(AffineTransform &at) {
	TextBox::draw(at);
}