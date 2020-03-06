#ifndef TWEEN_H
#define TWEEN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "DisplayObjectContainer.h"
#include "TweenableParams.h"
#include "TweenTransitions.h"


class Tween{ 

public:
	Tween(DisplayObjectContainer object);
    Tween(DisplayObjectContainer object, TweenTransitions transition);
    
    void animate(TweenableParams fieldtoAnimate, double startVal, double endVal, double time);

    void update();
    void isComplete(); 
    void setValue(TweenableParams param, double value);
private:

	
};

#endif