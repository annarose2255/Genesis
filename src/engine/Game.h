#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "DisplayObjectContainer.h"
#include "Camera.h"
#include "DisplayObject.h"
#include "ControllerManager.h"
#include "Event.h"
#include <vector>
#include <set>

using namespace std;

class Game : public DisplayObjectContainer {

public:
	
	/* Singleton pattern */
	static Game* instance;

	int frames_per_sec = 60;
	int windowWidth, windowHeight;
	static Camera* camera; 
	SDL_Window * window;
	static SDL_Renderer* renderer;

	//Global frame counter
	static unsigned int frameCounter;

	Game(int windowWidth, int windowHeight);
	virtual ~Game();
	virtual void start();

	virtual void update(set<SDL_Scancode> pressedKeys, set<SDL_GameControllerButton> pressedButtons, set<pair<SDL_GameControllerAxis, float>> movedAxis);
	virtual void draw(AffineTransform &at);
	set<SDL_Scancode> pressedKeys;
	set<SDL_GameControllerButton> pressedButtons;
	set<pair<SDL_GameControllerAxis, float>> movedAxis;
	SDL_GameController* controller;
	ControllerManager* controllerManager;

private:
	
	void initSDL();
	void quitSDL();
	
};

#endif
