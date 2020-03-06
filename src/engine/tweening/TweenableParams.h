#ifndef TWEENABLEPARAMS_H
#define TWEENABLEPARAMS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class TweenableParams{ 
    
public:
	//list of static final strings, e.g. X, Y, scale_x, etc
    TweenableParams();
    SDL_Point position; 
    static int width, height; 
    static int scaleX, scaleY; 
    static int rotation;
    SDL_Point pivot;
    static int alpha;
    bool visible;
    bool facingRight;
    
private:

	
};

#endif