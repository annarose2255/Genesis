#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Tween.h"
#include "AnimatedSprite.h"

Tween::Tween(AnimatedSprite* object) {
    this->object = object; //saves the object to be tweened
}
    
void Tween::animate(TweenableParams fieldToAnimate, double startVal, double endVal, double time){
    //saves the field to be tweened 
    //save the frameRate as well....to tween animated sprites 
    setValue(fieldToAnimate, startVal);
    
}

void Tween::update(){
    //if (!isComplete)
    //setValue(param, value);
    //update curTime 
    if (!isComplete()) {
        //TweenParam??
        setValue(param, value);
        curTime++;
    }

}
bool Tween::isComplete(){
    if (curTime == endTime) {
        return true;
    }
    else {
        return false;
    }
}
void Tween::setValue(TweenableParams param, double value){
    if (param.name == "position.x"){
        this->object->position.x = value;
    }
}