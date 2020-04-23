#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "AffineTransform.h"
#include <string>
#include "Player.h"
#include "MyGame.h"
#include "AnimatedSprite.h"
#include "Sprite.h"
#include "Game.h"
#include "Controls.h"
#include <fstream>
using namespace std;

class Enemy : public AnimatedSprite{
public:
//Here, "Sayu" is the player character
Enemy(Player* p);

void update(set<SDL_Scancode> pressedKeys, set<SDL_GameControllerButton> pressedButtons, set<pair<SDL_GameControllerAxis, float>> movedAxis);

void onMeleeStrike();

//void onEssenceStrike(Weapon* w);
void onCollision(DisplayObject* other);

void draw(AffineTransform &at);
void save(ofstream &out);

void charge();

void prepareCharge();

void setPatrolRange();

void patrol();

void moveToTarget();

bool isTargetReached();
int maxPatX;
int maxPatY;
int minPatX;
int minPatY;
int pauseCount = 0;
int targX;
int targY;
int vel = 0;
int maxVel = 4;
int acc = 0;
int rotVel = 0;
int rotAcc = 0;
int maxRotVel = 3;
int shield = 20;
bool clean =0;
int health = 20; //??
Player* player;
};

#endif
