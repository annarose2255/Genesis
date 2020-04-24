#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Sprite.h"
#include "AffineTransform.h"

using namespace std;

class TextBox : public Sprite {

public:

	// Make TextBox
	TextBox();
	TextBox(int numBoxes);
	~TextBox();

	virtual void update(set<SDL_Scancode> pressedKeys, set<SDL_GameControllerButton> pressedButtons, set<pair<SDL_GameControllerAxis, float>> movedAxis);
	virtual void draw(AffineTransform &at);

	void setText(string txt);
	void queueUp(string txt);
	void continueQueue();

	string text;
	int numBoxes;
	int maxChar=22;
	bool showLines=true;
	vector<TextBox*> boxes;
	vector<string> textQueue;

private:

	TTF_Font* font;
	SDL_Surface* surface;

};


#endif