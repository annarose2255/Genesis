#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Tween.h"
#include "AnimatedSprite.h"

Tween::Tween(AnimatedSprite* object) {
    this->object = object;
}

Tween::Tween(AnimatedSprite* object, TweenTransitions transition){

}
    
void Tween::animate(string fieldtoAnimate, double startVal, double endVal, double time){
    //within time, animate field from startVal to endVal
}

void Tween::update(){

}
void Tween::isComplete(){

}
void Tween::setValue(TweenableParams param, double value){
    
}