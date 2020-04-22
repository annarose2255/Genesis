#ifndef TWEEN_H
#define TWEEN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "DisplayObject.h"
#include "TweenParam.h"
#include "TweenableParams.h"
#include "TweenTransitions.h"
#include "AnimatedSprite.h"
// #include "Scene.h"

class Tween{ 

public:
	Tween(DisplayObject* object);
    // Tween(Scene* scene);
    ~Tween(); 
    void animate(TweenableParams fieldtoAnimate, double startVal, double endVal, double time);

    void update();
    bool isComplete(); 
    void setValue(TweenableParams param, double value);
    vector<TweenParam*> params;
private:
    DisplayObject* object;
    SDL_Texture* tex; 
    // Scene* scene;
	int curFrame = 0;
    int endFrame;
    // TweenableParams param; 
    TweenParam* tp; 
    double value, endVal;
};

#endif