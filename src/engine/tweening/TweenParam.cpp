#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "TweenParam.h"
#include "TweenableParams.h"
#include <iostream> 
using namespace std; 

TweenParam::TweenParam(TweenableParams paramToTween, double startVal, double endVal, double time){
    this->param = paramToTween; 
    this->startVal = startVal; 
    this->endVal = endVal; 
    this->newValue = startVal;
    this->time = time; 
    currentFrame = 0;
    endFrame = time * 24; 
    transition = new TweenTransitions(); 
}
TweenParam::~TweenParam() {
    delete transition; 
}
void TweenParam::calcValue(){
    //sends the TweenTransitions information to Tween 
    double percentDone = (double) currentFrame/endFrame; 
    // cout << "Percent Done" << percentDone << endl;
    this->transition->setVal(this->newValue, this->startVal, this->endVal);
    this->transition->easeIn = this->easeIn; 
    this->transition->applyTransition(percentDone);
    //save the newValue as the param's field 
    if (this->param.name == "alpha") {
        this->param.alpha = this->transition->getNewVal();
    }
    if (this->param.name == "position.x") {
        this->param.position.x = this->transition->getNewVal();
    }
    if (this->param.name == "position.y") {
        this->param.position.y = this->transition->getNewVal();
    }
     if (this->param.name == "scaleX") {
        this->param.scaleX = this->transition->getNewVal();
    }
    if (this->param.name == "scaleY") {
        this->param.scaleY = this->transition->getNewVal();
    }
    this->newValue = this->transition->getNewVal();

}
double TweenParam::getNewValue(){
    return this->newValue; 
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