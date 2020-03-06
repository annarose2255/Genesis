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
			this->update(pressedKeys);
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
		cout << event.type << endl;
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

void Game::update(set<SDL_Scancode> pressedKeys){
	frameCounter++;
	DisplayObjectContainer::update(pressedKeys);
}

void Game::draw(AffineTransform &at){
	SDL_RenderClear(Game::renderer);
	DisplayObjectContainer::draw(at);
	SDL_RenderPresent(Game::renderer);
}