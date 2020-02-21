#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Camera.h"

Camera::Camera(){
    SDL_Rect camera = { x, y, viewportWidth, viewportHeight };
    
}

Camera::~Camera(){

}