#ifndef TWEENTRANSITIONS_H
#define TWEENTRANSITIONS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


class TweenTransitions{ 
    
public:
	void applyTransition(double percentDone);
    void easeInOut(double percentDone); 
    //all the different transitions
    //include at least ONE non-linear transition
    
private:

	
};

#endif