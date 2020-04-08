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
	const int levelWidth = 1280;
	const int levelHeight = 960;
	
	static SDL_Rect camera;

	virtual void update(set<SDL_Scancode> pressedKeys,  ControllerInput controllerInput);
	virtual void draw(AffineTransform &at);

private:
	DisplayObject* bg;
	
};

#endif