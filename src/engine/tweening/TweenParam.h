#ifndef TWEENPARAM_H
#define TWEENPARAM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "TweenableParams.h"

class TweenParam{ 
    
public:
	TweenParam(TweenableParams paramToTween, double startVal, double endVal, double time);
    TweenableParams getParam();
    double getStartVal(); 
    double getEndVal(); 
    double getTweenTime();  
    
    
private:

	
};

#endif