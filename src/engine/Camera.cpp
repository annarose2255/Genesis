#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Camera.h"
#include "DisplayObject.h"

//http://lazyfoo.net/SDL_tutorials/lesson21/index.php
SDL_Rect Camera::camera = {0,0,800, 700}; //what you actual see
Camera::Camera(){
    

}
Camera::Camera(string filepath){
   
}

Camera::~Camera(){
    
}


void Camera::update(set<SDL_Scancode> pressedKeys,  ControllerInput controllerInput){
    DisplayObjectContainer::update(pressedKeys, controllerInput);
}

void Camera::draw(AffineTransform &at){
    DisplayObjectContainer::draw(at);

}