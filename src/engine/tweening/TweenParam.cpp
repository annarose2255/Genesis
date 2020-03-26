#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "TweenParam.h"
#include "TweenableParams.h"

TweenParam::TweenParam(TweenableParams paramToTween, double startVal, double endVal, double time){
    this->param = paramToTween; 
    this->startVal = startVal; 
    this->endVal = endVal; 
    this->time = time; 
}
TweenParam::TweenParam(TweenTransitions transition){
    //sends the TweenTransitions information to Tween 
    
}
TweenableParams TweenParam::getParam(){
    return this->param;
}
double TweenParam::getStartVal(){
    return this->startVal;
}
double TweenParam::getEndVal(){
    return this->endVal;
}
double TweenParam::getTweenTime(){
    return this->time;
} 