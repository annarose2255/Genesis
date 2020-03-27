#include <iostream>
#include "Game.h"
#include <string>
#include <ctime>
#include "DisplayObject.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

using namespace std;

SDL_Renderer* Game::renderer;
Game* Game::instance;
unsigned int Game::frameCounter = 0;


Game::Game(int windowWidth, int windowHeight){
	Game::instance = this;
	
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;

	initSDL();
	TTF_Init();
}

Game::~Game(){
	quitSDL();
}

void Game::quitSDL(){
	cout << "Quitting sdl" << endl;
	SDL_DestroyRenderer(Game::renderer);
	SDL_DestroyWindow(window);

	// Close controller
	if (controller){
		SDL_GameControllerClose(controller);
	}

	IMG_Quit();
	SDL_Quit();
}

void Game::initSDL(){
	// Initialize SDL
	if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK ) < 0){
		cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
	}
	IMG_Init(IMG_INIT_PNG);

	window = SDL_CreateWindow("myGame",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->windowWidth, this->windowHeight, 0);

	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

	Game::renderer = renderer;
}

void Game::start(){

	int ms_per_frame = (1.0/(double)this->frames_per_sec)*1000;
	std::clock_t start = std::clock();

	bool quit = false;
	SDL_Event event;

	// Check for controllers
	for (int i = 0; i < SDL_NumJoysticks(); ++i){
		if (SDL_IsGameController(i)) {
			controller = SDL_GameControllerOpen(i);
			if (controller) {
				cout << "Controller connected." << endl;
				controllerInput.connected = true;
				// only opens the first
				break;
			} else {
				cout << "Could not open gamecontroller" << endl;
				controllerInput.connected = false;
			}
		}
	}

	while(!quit){
		std::clock_t end = std::clock();
		double duration = (( end - start ) / (double) CLOCKS_PER_SEC)*1000;
		if(duration > ms_per_frame){
			start = end;
			this->update(pressedKeys, controllerInput);
			AffineTransform at;
			this->draw(at);
		}

		// cout << SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT) << endl;	

		// if (SDL_NumJoysticks() < 1){
		// 	cout << "Warning: No joysticks connected!" << endl;
		// 	controllerInput.connected = false;
		// } else {
		// 	// Load joystick
		// 	controller = SDL_JoystickOpen(0);
		// 	if (controller == NULL){
		// 		cout << "Warning: Unable to open game controller!" << endl;
		// 	}
		// 	controllerInput.connected = true;
		// }

		SDL_PollEvent(&event);
		// cout << event.type << endl;
		switch (event.type)
		{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				pressedKeys.insert(event.key.keysym.scancode);
				break;
			case SDL_KEYUP:
				pressedKeys.erase(event.key.keysym.scancode);
				break;
			// button events
			// case SDL_CONTROLLERBUTTONDOWN:
			case 1539:
				switch(event.cbutton.button){
					case SDL_CONTROLLER_BUTTON_A:
						controllerInput.a = true;
						cout << "pressed A" << endl;
						break;
					case SDL_CONTROLLER_BUTTON_B:
						controllerInput.b = true;
						cout << "pressed B" << endl;
						break;
				}
				break;
			// case SDL_CONTROLLERBUTTONUP:
			case 1540:
				switch(event.cbutton.button){
					case SDL_CONTROLLER_BUTTON_A:
						controllerInput.a = false;
						break;
					case SDL_CONTROLLER_BUTTON_B:
						controllerInput.b = false;
						break;
				}
				break;
			// axis events
			case SDL_CONTROLLERAXISMOTION:
				
				break;
			// device events
			case SDL_CONTROLLERDEVICEADDED:
				cout << "Device added." << endl;
				controller = SDL_GameControllerOpen(event.cdevice.which);
				controllerInput.connected = true;
				break;
			case SDL_CONTROLLERDEVICEREMOVED:
				cout << "Device removed." << endl;
				// probably should close controller too
				controller = NULL;
				controllerInput.connected = false;
				break;
		}

	}
}

void Game::update(set<SDL_Scancode> pressedKeys, ControllerInput controllerInput){
	frameCounter++;
	DisplayObjectContainer::update(pressedKeys, controllerInput);
}

void Game::draw(AffineTransform &at){
	SDL_RenderClear(Game::renderer);
	DisplayObjectContainer::draw(at);
	SDL_RenderPresent(Game::renderer);
}

bool Game::collision(DisplayObject* &displayObject1, DisplayObject* &displayObject2) {
	// get points for hitbox1 in global coordinate system
	AffineTransform gT1 = displayObject1->globalTransform();
	SDL_Point topLeft1 = gT1.transformPoint(0, 0);
	SDL_Point topRight1 = gT1.transformPoint(displayObject1->hitbox.width, 0);
	SDL_Point bottomRight1 = gT1.transformPoint(displayObject1->hitbox.width, displayObject1->hitbox.height);
	SDL_Point bottomLeft1 = gT1.transformPoint(displayObject1->hitbox.width, 0);

	// lines from those points
	Line l1 = {topLeft1, topRight1};
	Line l2 = {topRight1, bottomRight1};
	Line l3 = {bottomLeft1, bottomRight1};
	Line l4 = {topLeft1, bottomLeft1};

	Line displayObjectLines1[4] = {l1, l2, l3, l4};

	// get points for hitbox2 in global coordinate system
	AffineTransform gT2 = displayObject2->globalTransform();
	SDL_Point topLeft2 = gT2.transformPoint(0, 0);
	SDL_Point topRight2 = gT2.transformPoint(displayObject2->hitbox.width, 0);
	SDL_Point bottomRight2 = gT2.transformPoint(displayObject2->hitbox.width, displayObject2->hitbox.height);
	SDL_Point bottomLeft2 = gT2.transformPoint(displayObject2->hitbox.width, 0);

	// lines from those points
	Line l5 = {topLeft2, topRight2};
	Line l6 = {topRight2, bottomRight2};
	Line l7 = {bottomLeft2, bottomRight2};
	Line l8 = {topLeft2, bottomLeft2};

	Line displayObjectLines2[4] = {l5, l6, l7, l8};

	// see if any line intersects
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			// if any line intersects there is a collision
			if ( intersects(displayObjectLines1[i], displayObjectLines2[j]) ){
				return true;
			}
		}
	}
	return false;
}


// private helper method
bool Game::intersects(Line l1, Line l2) {
	// get orientations
	SDL_Point p1 = l1.pt1;
	SDL_Point q1 = l1.pt2;
	SDL_Point p2 = l2.pt1;
	SDL_Point q2 = l2.pt2;
	int o1 = getOrientation(p1, q1, p2);
	int o2 = getOrientation(p1, q1, q2);
	int o3 = getOrientation(p2, q2, p1);
	int o4 = getOrientation(p2, q2, q1);
	// if one orientation is the same then there is no intersection
	if ( o1 != o2  && o3 != o4 ){
		return true;
	// check if colinear
	} else if (o1 == 0 && o2 == 0 && o3 == 0 && o4 == 0){
		// check if one point is inbetween two other points using x projection
		// sort x values of one line
		int smallerX = p1.x;
		int largerX = q1.x;
		if (q1.x < smallerX){
			smallerX = q1.x;
			largerX = p1.x;
		}
		// see if either of the other line's points fall in between
		if ( (p2.x >= smallerX && p2.x <= largerX) || (q2.x >= smallerX && q2.x <= largerX) ){
			return true;
		}
	}
	return false;
}

int Game::getOrientation(SDL_Point p1, SDL_Point q1, SDL_Point p2) {
	float s1 = (q1.y - p1.y) / (q1.x - p1.x);
	float s2 = (p2.y - q1.y) / (p2.x - q1.x);
	if (s1 < s2){
		// turns left
		return 1;
	} else if (s2 < s1) {
		// turns right
		return 2;
	} else {
		// collinear
		return 0;
	}
}