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

void Sprite::update(set<SDL_Scancode> pressedKeys) {
    DisplayObjectContainer::update(pressedKeys);
}

<<<<<<< HEAD
void Sprite::draw(AffineTransform &at, SDL_Rect camera) {
    DisplayObjectContainer::draw(at, camera);
=======
void Sprite::draw(AffineTransform &at) {
    DisplayObjectContainer::draw(at);
>>>>>>> 28124d242415859506e8cf02a75402fa03d3229c
}