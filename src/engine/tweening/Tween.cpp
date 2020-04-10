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
    for (int i = 0; i < params.size(); i++) {
        delete params[i]; 
    }
}
void Tween::animate(TweenableParams fieldToAnimate, double startVal, double endVal, double time){
    //saves the field to be tweened 
    //save the frameRate as well....to tween animated sprites 
    TweenParam* temp = new TweenParam(fieldToAnimate, startVal, endVal, time);
    if (startVal > endVal) {
        temp->easeIn = false; 
    }
    else {
        temp->easeIn = true;
    }
    setValue(fieldToAnimate, startVal);
    this->endVal = endVal;
    endFrame = time * 24; //time * frames per sec 
    params.push_back(temp);
}

void Tween::update(){
    //if (!isComplete)
    //setValue(param, value);
    //update curTime 
    if (!isComplete()) {
        this->curFrame++;
        cout << "Tween Current Frame " << this->curFrame << endl;
        //increment TweenParam internal counter 
        for (int i = 0; i < params.size(); i++) {
            params[i]->currentFrame++;
            params[i]->calcValue(); 
            //set the object value to new value
            setValue(params[i]->getParam(), params[i]->getNewValue());
        }
    }
}
bool Tween::isComplete(){
    if (this->curFrame == this->endFrame) {
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
     if (param.name == "scaleX"){
        this->object->scaleX = value;
    }
    if (param.name == "scaleY"){
        this->object->scaleY = value;
    }
}