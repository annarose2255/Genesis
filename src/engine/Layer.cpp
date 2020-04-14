#include "Layer.h"
#include <iostream>

Layer::Layer() {

}
void Layer::update(set<SDL_Scancode> pressedKeys, set<SDL_GameControllerButton> pressedButtons, set<pair<SDL_GameControllerAxis, float>> movedAxis) {
    DisplayObjectContainer::update(pressedKeys, pressedButtons, movedAxis);
}

void Layer::draw(AffineTransform &at) {
    //pass scrollSpeed to the DisplayObjectContainer, which passes down to DisplayObject 
    DisplayObjectContainer::draw(at);
    setScrollSpeed(scrollSpeed);
}