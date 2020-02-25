#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Camera.h"

//http://lazyfoo.net/SDL_tutorials/lesson21/index.php
Camera::Camera(){
    camera = { x, y, viewportWidth, viewportHeight };

}
Camera::~Camera(){
    
}