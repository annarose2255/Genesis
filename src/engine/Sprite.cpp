#include "Sprite.h"

using namespace std;

Sprite::Sprite() : DisplayObjectContainer() {
    this->type = "Sprite";
}

Sprite::Sprite(string id, string filepath) : DisplayObjectContainer(id, filepath){
    this->type = "Sprite";
}

Sprite::Sprite(string id, int red, int green, int blue) : DisplayObjectContainer(id, red, green, blue) {
    this->type = "Sprite";
}

void Sprite::update(set<SDL_Scancode> pressedKeys, set<SDL_GameControllerButton> pressedButtons, set<pair<SDL_GameControllerAxis, float>> movedAxis) {
    DisplayObjectContainer::update(pressedKeys, pressedButtons, movedAxis);
}


void Sprite::draw(AffineTransform &at) {
    DisplayObjectContainer::draw(at);
}