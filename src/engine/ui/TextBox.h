#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Sprite.h"
#include "AffineTransform.h"

using namespace std;

class TextBox : public Sprite {

public:

	// Make TextBox
	TextBox(int red, int green, int blue);

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

	string text;

private:

};


#endif