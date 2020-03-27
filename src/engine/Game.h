#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "DisplayObjectContainer.h"
#include "DisplayObject.h"
#include <vector>
#include <set>

using namespace std;

struct Line {
	SDL_Point pt1;
	SDL_Point pt2;
};

class Game : public DisplayObjectContainer {


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

	virtual void update(set<SDL_Scancode> pressedKeys, ControllerInput controllerInput);
	virtual void draw(AffineTransform &at);
	set<SDL_Scancode> pressedKeys;
	ControllerInput controllerInput;
	SDL_GameController* controller;
	bool collision(DisplayObject* &displayObject1, DisplayObject* &displayObject2);

private:
	
	void initSDL();
	void quitSDL();
	int getOrientation(SDL_Point p1, SDL_Point q1, SDL_Point p2);
	bool intersects(Line l1, Line l2);
	
};

#endif
