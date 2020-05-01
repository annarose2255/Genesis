#ifndef ROOMSAVE_H
#define ROOMSAVE_H

#include "DisplayObject.h"
#include "Player.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

class RoomSave {

public:
	
    Player* player; 
    int roomNum; 
    map<string, DisplayObject*> enemies; 
    map<string, DisplayObject*> objects;
    string tileFilePath;

private:
};

#endif