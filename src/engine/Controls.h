#ifndef CONTROLS_H
#define CONTROLS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "DisplayObjectContainer.h"
#include "Camera.h"
#include "DisplayObject.h"
#include "Event.h"
#include <vector>
#include <set>

using namespace std;

class Controls  {

public:
    Controls();
	void key(set<SDL_Scancode> pressedKeys, set<SDL_GameControllerButton> pressedButtons, set<pair<SDL_GameControllerAxis, float>> movedAxis);
    bool holdRight();//method that returns if the player is moving right
    bool holdLeft();//method that returns if player is moving left
    bool pressJump();//returns if the character has had jump pressed

private:
	set<SDL_Scancode> keys;
    set<SDL_GameControllerButton> buttons;
    set<pair<SDL_GameControllerAxis, float>> axis;

};

#endif
