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
	TextBox(int red, int green, int blue);
	~TextBox();

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

	void setText(string txt);

	string text;

private:

	TTF_Font* font;
	SDL_Surface* surface;

};


#endif