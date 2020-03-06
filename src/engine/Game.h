#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "DisplayObjectContainer.h"
#include <vector>
#include <set>

using namespace std;

class Game : public DisplayObjectContainer {

struct ControllerInput {
	bool connected = false;
	bool a = false;
	bool b = false;
	bool x = false;
	bool y = false;
	bool leftDpad = false;
	bool rightDpad = false;
	bool upDpad = false;
	bool downDpad = false;
	int leftStickX = 0;
	int rightStickX = 0;
	int leftStickY = 0;
	int rightStickY = 0;
};

public:

	/* Singleton pattern */
	static Game* instance;

	int frames_per_sec = 60;
	int windowWidth, windowHeight;

	SDL_Window * window;
	static SDL_Renderer* renderer;

	//Global frame counter
	static unsigned int frameCounter;

	Game(int windowWidth, int windowHeight);
	virtual ~Game();
	virtual void start();

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);
	set<SDL_Scancode> pressedKeys;
	ControllerInput controllerInput;
	SDL_GameController* controller;

private:

	void initSDL();
	void quitSDL();
	
};

#endif
