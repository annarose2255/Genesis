#include <iostream>
#include "Game.h"
#include <string>
#include <ctime>
#include "DisplayObject.h"
#include "EventDispatcher.h"
#include "Event.h"
#include "ControllerEvent.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

using namespace std;

SDL_Renderer* Game::renderer;
Game* Game::instance;
unsigned int Game::frameCounter = 0;
Camera* Game::camera = new Camera();


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
	if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_HAPTIC ) < 0){
		cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
	}
	IMG_Init(IMG_INIT_PNG);

	window = SDL_CreateWindow("myGame",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->windowWidth, this->windowHeight, 0);

	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

	Game::renderer = renderer;
}

void Game::start(){
	// initiale Event Dispatcher
	EventDispatcher* eDispatcher = EventDispatcher::getInstance();
	controllerManager = new ControllerManager();
	eDispatcher->addEventListener(controllerManager, CONTROLLER_ADDED_EVENT);

	int ms_per_frame = (1.0/(double)this->frames_per_sec)*1000;
	std::clock_t start = std::clock();

	bool quit = false;
	SDL_Event event;

	
	// Check for controllers
	for (int i = 0; i < SDL_NumJoysticks(); ++i){
		if (SDL_IsGameController(i)) {
			controller = SDL_GameControllerOpen(i);
			if (controller) {
				EventDispatcher::getInstance()->dispatchEvent(new ControllerEvent(CONTROLLER_ADDED_EVENT, EventDispatcher::getInstance(), controller));				
				break;
			} else {
				cout << "Could not open gamecontroller" << endl;
			}
		}
	}

	while(!quit){
		std::clock_t end = std::clock();
		double duration = (( end - start ) / (double) CLOCKS_PER_SEC)*1000;
		if(duration > ms_per_frame){
			start = end;
			this->update(pressedKeys, pressedButtons);
			AffineTransform at;
			// SDL_Rect camera; 
			this->draw(at);
		}

		SDL_PollEvent(&event);
		// cout << event.type << endl;
		// cout << event.type << endl;
		// cout << SDL_CONTROLLERBUTTONDOWN << endl;
		// cout << SDL_CONTROLLER_BUTTON_DPAD_DOWN << endl;
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
			case SDL_JOYAXISMOTION:
				// if ((event.jaxis.value < -3200) || (event.jaxis.value > 3200)) {
				// 	if( event.jaxis.axis == 0) 
				// 	{
				// 		if (event.jaxis.value < -3200){
				// 			pressedButtons.insert(SDL_CONTROLLER_BUTTON_DPAD_LEFT);
				// 		}
						
				// 	}

				// 	if( event.jaxis.axis == 1) 
				// 	{
				// 		/* Up-Down movement code goes here */
				// 	}
				// }
				break;
			case SDL_JOYBUTTONDOWN:
				//cout << "JOYDOWN IS TRIGGERED" << endl;
				pressedButtons.insert((SDL_GameControllerButton) event.jbutton.button);
				break;
			case SDL_JOYBUTTONUP:
				pressedButtons.erase((SDL_GameControllerButton) event.jbutton.button);
				break;
			case SDL_CONTROLLERAXISMOTION:
				break;
			case SDL_CONTROLLERBUTTONDOWN:
				//cout << "CONTROLLER down has been triggered" << endl;
				pressedButtons.insert((SDL_GameControllerButton) event.cbutton.button);
				break;
			case SDL_CONTROLLERBUTTONUP:
				pressedButtons.erase((SDL_GameControllerButton) event.cbutton.button);
				break;
			// device events
			case SDL_CONTROLLERDEVICEADDED:
				controller = SDL_GameControllerOpen(event.cdevice.which);
				EventDispatcher::getInstance()->dispatchEvent(new ControllerEvent(CONTROLLER_ADDED_EVENT, EventDispatcher::getInstance(), controller));	
				break;
			case SDL_CONTROLLERDEVICEREMOVED:
				EventDispatcher::getInstance()->dispatchEvent(new ControllerEvent(CONTROLLER_REMOVED_EVENT, EventDispatcher::getInstance(), controller));	
				break;
		}

	}
}

void Game::update(set<SDL_Scancode> pressedKeys, set<SDL_GameControllerButton> pressedButtons){
	frameCounter++;
	DisplayObjectContainer::update(pressedKeys, pressedButtons);
}


void Game::draw(AffineTransform &at){
	SDL_RenderClear(Game::renderer);
	DisplayObjectContainer::draw(at);
	//render camera here 
	SDL_RenderPresent(Game::renderer);
}