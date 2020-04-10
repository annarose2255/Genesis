#ifndef MENUITEM_H
#define MENUITEM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Sprite.h"
#include "AffineTransform.h"
#include "TextBox.h"
#include "SelectionMenu.h"

using namespace std;

class MenuItem : public TextBox {

public:

	// Make Menu Item
	MenuItem(string name, int posX, int posY);
	~MenuItem();

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

	// To keep track of which menu to go to !
	// ie. Selecting "Items" -> ItemsMenu
	SelectionMenu* nextMenu;
	SelectionMenu* prevMenu;

private:

};


#endif