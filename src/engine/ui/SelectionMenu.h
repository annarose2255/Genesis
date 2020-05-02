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

	virtual void update(set<SDL_Scancode> pressedKeys, set<SDL_GameControllerButton> pressedButtons, set<pair<SDL_GameControllerAxis, float>> movedAxis);
	virtual void draw(AffineTransform &at);

	void addItem(MenuItem* item);
	MenuItem* getItem(int index);
	void selectItem(int ind);
	void goBack();
	int selectInd;
	bool selectedaitem = false;
	int counter_for_pressing = 0;
	bool enemyTurn = false;
	bool decideFate = false;
	bool betweenturns = false;
	int enterframe = 0;
	bool death = false;
	bool fakeboss = false;
	bool canSelect = true;
private:

	vector<MenuItem*> menuItems;
	MenuItem* prevItem;


};


#endif