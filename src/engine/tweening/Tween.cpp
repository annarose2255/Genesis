#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Tween.h"
#include "DisplayObject.h"

Tween::Tween(DisplayObject* object) {
    // DisplayObject* obj = dynamic_cast<DisplayObject*>(object);
    this->object = object; //saves the object to be tweened
}

// Tween::Tween(Scene* scene) { //for scenes
//     this->scene = scene; //saves the object to be tweened
// }

Tween::~Tween() {
    delete tp; 
}
void Tween::animate(TweenableParams fieldToAnimate, double startVal, double endVal, double time){
    //saves the field to be tweened 
    //save the frameRate as well....to tween animated sprites 
    this->tp = new TweenParam(fieldToAnimate, startVal, endVal, time);
    setValue(fieldToAnimate, startVal);
    this->endVal = endVal;
    endFrame = time * 24; //time * frames per sec 
}

void Tween::update(){
    //if (!isComplete)
    //setValue(param, value);
    //update curTime 
    if (!isComplete()) {
        this->curFrame++;
        cout << "Tween Current Frame " << this->curFrame << endl;
        //increment TweenParam internal counter 
        this->tp->currentFrame++;
        this->tp->calcValue(); 
        //set the object value to new value
        setValue(this->tp->getParam(), this->tp->getNewValue());
        // this->tex = this->object->getTexture();
        //draw the object with the new value 
        // DisplayObject::setTexture(this->tex);
    }
}
bool Tween::isComplete(){
    if (this->curFrame == this->endFrame || this->tp->getNewValue() >= this->endVal) {
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
    if (param.name == "position.y"){
        this->object->position.y = value;
    }
    if(param.name == "alpha"){
        this->object->alpha = value;
    }
}