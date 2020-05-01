#ifndef GAMESAVE_H
#define GAMESAVE_H

#include "DisplayObject.h"
#include "Player.h"
#include "RoomSave.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

class GameSave {

public:
	
	GameSave();
	void write(string filepath);
    void addRoom(RoomSave* rm);
    bool loadedRoom(int roomNum);
    map<int, RoomSave*> savedRooms;
private:

};

#endif