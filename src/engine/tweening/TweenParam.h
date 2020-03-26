#ifndef TWEENPARAM_H
#define TWEENPARAM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "TweenableParams.h"
#include "TweenTransitions.h"

class TweenParam{ 
    
public:
	TweenParam(TweenableParams paramToTween, double startVal, double endVal, double time);
    TweenParam(TweenTransitions transition);
    TweenableParams getParam();
    double getStartVal(); 
    double getEndVal(); 
    double getTweenTime();  
    
private:
    TweenableParams param; 
    double startVal, endVal, time;
    int currentFrame, maxFrame; 
	
};

#endif