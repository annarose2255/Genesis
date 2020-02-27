#ifndef CAMERA_H
#define CAMERA_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Camera{ 

public:
	Camera();
	~Camera();

	SDL_Rect camera;

	int x = 0;
	int y = 0;
	int viewportWidth = 800;
	int viewportHeight = 700;
	//Limits -> viewportWidth and Height is reached, stop scrolling

	//The dimensions of the level
	const int LEVEL_WIDTH = 1280;
	const int LEVEL_HEIGHT = 960;

private:

	
};

#endif