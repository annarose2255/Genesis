#ifndef TWEENJUGGLER_H
#define TWEENJUGGLER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "DisplayObjectContainer.h"
#include "Tween.h"

class TweenJuggler{ 

public:
	TweenJuggler();
    void add(Tween tween);
    void nextFrame();
    
private:
    int currentFrame;
	
};

#endif