#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "TweenJuggler.h"
#include <iostream>

using namespace std;

TweenJuggler::TweenJuggler(){

}
void TweenJuggler::add(Tween* tween){
    //adds to the Queue
    queue.push_back(tween);
}
void TweenJuggler::nextFrame(){
    for (int i = 0; i < queue.size(); i++) {
        if (!queue[i]->isComplete()) {
            // cout << "queue is not complete!" << endl;
            queue[i]->update();
            // cout << "out of queue update!" << endl;
        }
        else {
            queue.erase(queue.begin() + i);
        }
    }
    currentFrame++;
}