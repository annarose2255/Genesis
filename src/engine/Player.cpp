#include <iostream>
#include <cstdlib>
#include "Player.h"
#include "MyGame.h"
#include "AnimatedSprite.h"
#include "Sprite.h"
#include "Game.h"
#include "Controls.h"

using namespace std;


Player::Player() : AnimatedSprite("Player"){

	this->type = "Player";
	this->id = "Null";
	
	this->position.x = 55;
	this->position.y = 200;
	this->width = 416;
	this->height = 454;
	this->scaleX = 0.15;
	this->scaleY = 0.15;
	this->pivot.x = this->width / 2;
	this->pivot.y = this->height / 2;

	this->addAnimation("resources/PlayerSprites/", "Idle", 16, 4, true);
	this->addAnimation("resources/PlayerSprites/", "Run", 20, 2, true);
	this->addAnimation("resources/PlayerSprites/", "Jump", 30, 1, false);
	this->play("Idle");
}
Player::Player(string id){
	this->type = "Player";
	this->id = id;
	
	this->position.x = 55;
	this->position.y = 200;
	this->width = 416;
	this->height = 454;
	this->scaleX = 0.15;
	this->scaleY = 0.15;
	this->pivot.x = this->width / 2;
	this->pivot.y = this->height / 2;

	this->addAnimation("resources/PlayerSprites/", "Idle", 16, 4, true);
	this->addAnimation("resources/PlayerSprites/", "Run", 20, 2, true);
	this->addAnimation("resources/PlayerSprites/", "Jump", 30, 1, false);
	this->play("Idle");
}
Player::Player(string id, string spriteSheetPath, string xmlPath) : AnimatedSprite(id,  spriteSheetPath,  xmlPath){
	this->type = "Player";

	//this = a;
}

//Called automatically by collision system when something collides with the player
//our job is to simply react to that collision.
 void Player::onCollision(DisplayObject* other){
	 if(other->type == "Platform"){
		//MyGame::collisionSystem.resolveCollision(this, other, this->position.x - oldX, this->position.y - oldY);	
		cout<<"ydelta in: "<< this->position.y - oldY<<endl;
		MyGame::collisionSystem->resolveCollision(this, other, this->position.x - oldX, this->position.y - oldY,
			0, 0);
		//MyGame::collisionSystem->resolveCollision
		//this->collideing = true;
		//DisplayObject::onCollision(other);
		this->_yVel = 0;
		//_yAccCount= 0;
		this->standing=true;
	}
	/* else if(other->type == "Enemy"){
		if(!this->iFrames){
			this->onEnemyCollision((Enemy*)other);
		}
	}*/

}
void Player::setState(string newstate){
	state = newstate;
}

void Player::update(set<SDL_Scancode> pressedKeys, set<SDL_GameControllerButton> pressedButtons, set<pair<SDL_GameControllerAxis, float>> movedAxis){
	AnimatedSprite::update(pressedKeys, pressedButtons, movedAxis);
	oldY = this->position.y;
	oldX = this->position.x;
	this->prevPos.x = oldX;
	this->prevPos.y = oldY;
	//cout<<"position y: "<<this->position.y<<endl;
	//Movement arrow keys
	//Controls is a class we wrote that just checks the SDL Scancode values and game controller values in one check
	if(MyGame::controls->holdRight()){
		this->position.x += 2;
		this->facingRight = true;
		if(this->standing){
			this->play("Run");
		}
	}
	else if(MyGame::controls->holdLeft()){
		this->position.x -= 2;
		this->facingRight = false;
		if(this->standing){
			this->play("Run");
		}
	} 
	
	
	//play idle animation if player is just standing still on ground
	if(this->standing && !MyGame::controls->holdLeft() && !MyGame::controls->holdRight()){
		this->play("Idle");
	} 
	

	/* handle iFrames if player was hit by enemy recently */
	if(this->iFrames){
		this->visible = this->iFrameCount%2 == 0;
		this->iFrameCount++;
		if(this->iFrameCount == this->numIFrames){
			this->iFrames = false;
			this->visible = true;
		}
	}

	/* Calculate fall velocity */

	//if (!this->_standing){ //&& this->collideing == false){
		//cout<<"falling"<<endl;
	_yAccCount++;
	if(_yAccCount == _yAcc){
		_yAccCount=0;
		this->_yVel++;
		if(this->_yVel > _maxFall) this->_yVel = _maxFall;
	}

	//}

	/* /* Jumping */
	if(this->standing && MyGame::controls->pressJump()){ //_standing &&
	cout<<"jump"<<endl;
		this->_yVel = _jumpVel;
		this->standing = false;
		this->play("Jump");
		jump_buffer_start = true;
	}
	if(this->standing){
		jump_buffer_start = false;
		jump_buffer = 0;
	}
	if (jump_buffer_start == true){
		jump_buffer++;
	}
	if(this->state == "MovAblStart"){
		state_cooldown_counter++;
		//cout<<"cooldown: "<<state_cooldown_counter<<endl;
		if (!this->standing && MyGame::controls->pressJump() && activated == false && jump_buffer %4 == 0){
			cout<<"double"<<endl;
			this->_yVel = _jumpVel;
			this->play("Jump");
			activated = true;
		}
	}
	if (state_cooldown_counter == 200){
		cout<<"state_cooldown_counter == 200"<<endl;
		this->state = "normal";
		activated = false;
		state_cooldown_counter = 0;
	}
	/* Actual falling depending on falling versus whether a jump occurred */
	this->position.y += this->_yVel;
}

/*void Player::onEnemyCollision(Enemy* enemy){
	this->health -= enemy->damage;
	this->initIFrames(120);
}*/

void Player::initIFrames(int numFrames){
	this->iFrameCount = 0;
	this->numIFrames = numFrames;
	this->iFrames = true;
}

void Player::draw(AffineTransform &at){
	AnimatedSprite::draw(at);
}
