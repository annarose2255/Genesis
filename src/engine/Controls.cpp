#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "DisplayObjectContainer.h"
#include "Camera.h"
#include "DisplayObject.h"
#include "Event.h"
#include "Controls.h"
#include <vector>
#include <set>

using namespace std;

Controls::Controls(){
    set<SDL_Scancode> pressedKeys;
     set<SDL_GameControllerButton> pressedButtons; 
     set<pair<SDL_GameControllerAxis, float>> movedAxis;
    keys = pressedKeys;
    buttons = pressedButtons;
    axis = movedAxis;

}
void Controls::key(set<SDL_Scancode> pressedKeys, set<SDL_GameControllerButton> pressedButtons, set<pair<SDL_GameControllerAxis, float>> movedAxis){
    keys = pressedKeys;
    buttons = pressedButtons;
    axis = movedAxis;
}
    //method that returns if the player is moving right
bool Controls::holdRight(){
    if (keys.find(SDL_SCANCODE_D) != keys.end()){ //|| axis.find.find(SDL_CONTROLLER_AXIS_RIGHTX) != axis.end()){ //DONT KNOW IF CONTROLLER PART WORKS
        return true;
    }
    else{
        return false;
    }
}
//method that returns if player is moving left
bool Controls::holdLeft(){
     if (keys.find(SDL_SCANCODE_A) != keys.end()){ //|| axis.find.find(SDL_CONTROLLER_AXIS_LEFTX) != axis.end()){
         return true;
     }
    return false;
}
//returns if the character has had jump pressed
bool Controls::pressJump(){
     if (keys.find(SDL_SCANCODE_SPACE) != keys.end() || buttons.find(SDL_CONTROLLER_BUTTON_A) != buttons.end()){
         return true;
     }
    return false;
}

