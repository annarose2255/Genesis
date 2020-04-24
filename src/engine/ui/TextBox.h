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
	~TextBox();

	virtual void update(set<SDL_Scancode> pressedKeys, set<SDL_GameControllerButton> pressedButtons, set<pair<SDL_GameControllerAxis, float>> movedAxis);
	virtual void draw(AffineTransform &at);

	void setText(string txt);

	string text;
	bool decideFate = false;
private:
	TTF_Font* font;
	SDL_Surface* surface;

};


#endif