#ifndef CAMERA_H
#define CAMERA_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "DisplayObjectContainer.h"
#include "DisplayObject.h"

class Camera: public DisplayObjectContainer{ 

public:
	Camera();
	Camera(string filepath);
	~Camera();

	int x = 0;
	int y = 0;
	int viewportWidth = 800;
	int viewportHeight = 700;
	//Limits -> viewportWidth and Height is reached, stop scrolling

	//The dimensions of the level
	const int LEVEL_WIDTH = 1280;
	const int LEVEL_HEIGHT = 960;


	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at, SDL_Rect camera);

private:
	DisplayObject* bg;
	
};

#endif