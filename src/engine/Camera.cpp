#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Camera.h"
#include "DisplayObject.h"

//http://lazyfoo.net/SDL_tutorials/lesson21/index.php
Camera::Camera(){
    

}
Camera::Camera(string filepath){
   
}

Camera::~Camera(){
    
}


void Camera::update(set<SDL_Scancode> pressedKeys){
    DisplayObjectContainer::update(pressedKeys);
}

void Camera::draw(AffineTransform &at, SDL_Rect camera){
    DisplayObjectContainer::draw(at, camera);

}