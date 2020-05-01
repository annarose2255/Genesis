#ifndef MENUITEM_H
#define MENUITEM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Sprite.h"
#include "AffineTransform.h"
#include "TextBox.h"
#include "SelectionMenu.h"
#include "Event.h"
#include "EventDispatcher.h"

using namespace std;

class MenuItem : public TextBox {

public:

	// Make Menu Item
	MenuItem(string name, int posX, int posY);
	MenuItem(string name, int posX, int posY, Event* e);
	~MenuItem();

	virtual void update(set<SDL_Scancode> pressedKeys, set<SDL_GameControllerButton> pressedButtons, set<pair<SDL_GameControllerAxis, float>> movedAxis);
	virtual void draw(AffineTransform &at);

	void setAction(Event* e);
	void action(EventDispatcher* ed);
	Event* getAction();
	string getName();
	// To keep track of which menu to go to !
	// ie. Selecting "Items" -> ItemsMenu
	SelectionMenu* nextMenu;
	SelectionMenu* prevMenu;
	string name;

	Event* itemAction;

private:

};


#endif