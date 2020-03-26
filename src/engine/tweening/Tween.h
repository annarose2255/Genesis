#ifndef TWEEN_H
#define TWEEN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "DisplayObjectContainer.h"
#include "TweenableParams.h"
#include "TweenTransitions.h"
#include "AnimatedSprite.h"


class Tween{ 

public:
	Tween(AnimatedSprite* object);
    
    void animate(TweenableParams fieldtoAnimate, double startVal, double endVal, double time);

    void update();
    bool isComplete(); 
    void setValue(TweenableParams param, double value);
private:
    AnimatedSprite* object;
	double curTime;
    double endTime;
    TweenableParams param; 
    double value;
};

#endif