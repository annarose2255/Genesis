#ifndef TWEENABLEPARAMS_H
#define TWEENABLEPARAMS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
using namespace std; 

class TweenableParams{ 
    
public:
	//list of static final strings, e.g. X, Y, scale_x, etc
    string name;
    SDL_Point position; 
    int width, height; 
    int scaleX, scaleY; 
    int rotation;
    SDL_Point pivot;
    int alpha;
    
private:

	
};

#endif