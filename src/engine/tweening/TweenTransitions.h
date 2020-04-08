#ifndef TWEENTRANSITIONS_H
#define TWEENTRANSITIONS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


class TweenTransitions{ 
    
public:
    TweenTransitions();
	void applyTransition(double percentDone);
    void easeInOut(double percentDone); 
    //all the different transitions
    //include at least ONE non-linear transition
    void setVal(double current, double start, double end);
    double getNewVal();
    bool easeIn;
private:
    double curVal, startVal, endVal;
    int startTime, endTime; 
    double newValue;
	
};

#endif