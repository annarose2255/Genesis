#ifndef MYGAME_H
#define MYGAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Game.h"
#include "LTexture.h"
#include "DisplayObject.h"


using namespace std;

class MyGame {

public:
	//The dimensions of the level
	const int LEVEL_WIDTH = 1280;
	const int LEVEL_HEIGHT = 960;

	//Screen dimension constants
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;
	//Starts up SDL and creates window
	bool init();

	//Loads media
	bool loadMedia();

	//Frees media and shuts down SDL
	void close();

	//Loads individual image as texture
	// SDL_Texture * loadTexture( std::string path );

	//The window we'll be rendering to
	SDL_Window* gWindow = NULL;

	//The window renderer
	SDL_Renderer* gRenderer = NULL;

	// //Current displayed texture
	// SDL_Texture* gTexture = NULL;
	//Scene textures
	LTexture gDotTexture;
	LTexture gBGTexture;
	

};

#endif