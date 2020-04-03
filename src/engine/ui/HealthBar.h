#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Sprite.h"
#include "AffineTransform.h"

using namespace std;

class HealthBar : public Sprite{

public:
	
	//make a health bar, set its rgb color
	HealthBar(int red, int green, int blue);

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

	void setInstant(int value);
	

	//these determine the maximum value of the bar, the current value (e.g., 30 health out of 100)
	//speed is how fast the bar fills and shrinks when changing values.
	int maxVal = 100;
	int curVal = 100;
	int speed = 1;


private:

	//pointer to the actual fill sprite rectangle.
	Sprite* fill;
};

#endif