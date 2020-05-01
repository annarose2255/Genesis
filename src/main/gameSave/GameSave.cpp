#include "GameSave.h"

GameSave::GameSave() {

}
void GameSave::addRoom(RoomSave* rm) {
     savedRooms.insert(std::pair<int, RoomSave*>(rm->roomNum, rm));
}
void GameSave::write(string filepath){

}
