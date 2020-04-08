#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "TweenTransitions.h"
#include <iostream> 
using namespace std; 
TweenTransitions::TweenTransitions() {

}
void TweenTransitions::applyTransition(double percentDone){
    easeInOut(percentDone);
}
void TweenTransitions::easeInOut(double percentDone){
    //newvalue = (end - begin) * ((double) SDL_GetTicks() - started)/ duration + begin 
    //linear 
    this->newValue = this->curVal + (int) (this->endVal * percentDone); 
    if (this->newValue > this->endVal) {
        this->newValue = this->endVal; 
    }
    cout << "Transitions cur Val " << this->curVal << endl;
    cout << "Transitions end Val " << this->endVal << endl;
    cout << "Transitions new Val "<< this->newValue << endl;
    //quad 
    //cubic 
    //log 
}
double TweenTransitions::getNewVal(){
    return this->newValue;
}
void TweenTransitions::setVal(double current, double end){
    this->curVal = current;
    this->endVal = end; 
    cout << "set curVal " << this->curVal << endl; 
    cout << "set endVal " << this->endVal << endl;
}