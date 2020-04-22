#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "AnimatedSprite.h"
#include <vector>
#include <string>
#include <fstream>
#include "Sprite.h"

using namespace std;

class Player : public AnimatedSprite{

public:
	Player();
	Player(string id);
	Player(string id, string spriteSheetPath, string xmlPath);

	virtual void update(set<SDL_Scancode> pressedKeys, set<SDL_GameControllerButton> pressedButtons, set<pair<SDL_GameControllerAxis, float>> movedAxis);
	virtual void draw(AffineTransform &at);

	//void onEnemyCollision(Enemy* enemy);
	virtual bool onCollision(DisplayObject* other);

	//set state 
	void setState(string newstate); //sets the state of the character 

	/* Health and such */
	int health = 100;
	int maxHealth = 100;

	//iFrames
	bool iFrames = false;
	int iFrameCount = 0;
	int numIFrames = 0;

	/* Current Enemy player is engaging with*/
	//Enemy* curEnemy = NULL;

private:

	int oldX=0, oldY=0;
	int jump_buffer = 0; //#of tiks till can jump
	bool jump_buffer_start = false; //var to start buffer
	int _jumpVel = -10;
	int state_combat_cooldown_counter= 0;//var for the time of cooldown for combat ability
	int state_mov_cooldown_counter= 0;//var for the time of cooldown for mov ability
	bool activated = false; //var for if the ability has been activated
	set<string> activestates = {};
	SDL_Texture* normaltexture;
	SDL_Texture* shieldtexture;
	int sprint = 0;//var to make you go faster
	//string state;
	/* Falling variables */
	//bool _standing = false;
	int _maxFall = 9;
	int _yAcc = 2; //one pixel every two frames
	int _yAccCount = 0;
	//int _yVel = 0;

	void initIFrames(int numFrames);

};

#endif