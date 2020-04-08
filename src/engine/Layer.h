#ifndef LAYER_H
#define LAYER_H

#include "DisplayObject.h"
#include "DisplayObjectContainer.h"
#include "Sprite.h"
#include "AnimatedSprite.h"

#include <string>
#include <vector>

using namespace std;

class Layer : public DisplayObjectContainer {

public:
    Layer();
    double scrollSpeed;

    virtual void update(set<SDL_Scancode> pressedKeys,  ControllerInput controllerInput);
	virtual void draw(AffineTransform &at);
private:

};

#endif
