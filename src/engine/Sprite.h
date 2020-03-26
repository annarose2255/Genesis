#ifndef SPRITE_H
#define SPRITE_H

#include "DisplayObjectContainer.h"

using namespace std;

class Sprite : public DisplayObjectContainer{

public:
	
	Sprite();
	Sprite(string id, string filepath);
	Sprite(string id, int red, int green, int blue);

	virtual void update(set<SDL_Scancode> pressedKeys);
<<<<<<< HEAD
	virtual void draw(AffineTransform &at, SDL_Rect camera);
=======
	virtual void draw(AffineTransform &at);
>>>>>>> 28124d242415859506e8cf02a75402fa03d3229c

private:
	
};

#endif