#ifndef SELECTIONMENU_H
#define SELECTIONMENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Sprite.h"
#include "AffineTransform.h"

using namespace std;

class MenuItem;

class SelectionMenu : public Sprite {

public:

	// Make Selection Menu
	SelectionMenu();
	~SelectionMenu();

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

	void addItem(MenuItem* item);
	void selectItem(int ind);
	void goBack();

private:

	vector<MenuItem*> menuItems;
	MenuItem* prevItem;
	int selectInd;

};


#endif