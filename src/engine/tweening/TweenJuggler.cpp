#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "TweenJuggler.h"

TweenJuggler::TweenJuggler(){

}
void TweenJuggler::add(Tween* tween){
    //adds to the Queue
    queue.push_back(tween);
}
void TweenJuggler::nextFrame(){
    for (int i; i < queue.size(); i++) {
        if (!queue[i]->isComplete()) {
            queue[i]->update();
        }
        else {
            queue.erase(queue.begin() + i);
        }
    }
    currentFrame++;
}