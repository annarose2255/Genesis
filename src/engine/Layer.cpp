#include "Layer.h"
#include <iostream>

Layer::Layer() {

}
void Layer::update(set<SDL_Scancode> pressedKeys) {
    DisplayObjectContainer::update(pressedKeys);
}

void Layer::draw(AffineTransform &at) {
    //pass scrollSpeed to the DisplayObjectContainer, which passes down to DisplayObject 
    DisplayObjectContainer::draw(at);
    setScrollSpeed(scrollSpeed);
}