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

	this->addAnimation("resources/ghostchar/", "Idle", 6, 4, true);
	this->addAnimation("resources/ghostchar/", "run", 6, 2, true);
	this->addAnimation("resources/ghostchar/", "jump", 6, 1, false);
	this->addAnimation("resources/ghostchar/", "Death", 6, 1, false);
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

	this->addAnimation("resources/ghostchar/", "Idle", 6, 4, true);
	this->addAnimation("resources/ghostchar/", "run", 6, 2, true);
	this->addAnimation("resources/ghostchar/", "jump", 6, 1, false);
	this->addAnimation("resources/ghostchar/", "Death", 6, 1, false);
	this->play("Idle");
}
Player::Player(string id, bool isSheet) : AnimatedSprite(id, true){
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

	this->addSSAnimation("resources/ghostchar/idle.png", "resources/ghostchar/idle.xml", 12, true);
	this->addSSAnimation("resources/ghostchar/run.png", "resources/ghostchar/run.xml", 2, true);
	this->addSSAnimation("resources/ghostchar/jump.png", "resources/ghostchar/jump.xml", 1, false);
	this->addSSAnimation("resources/ghostchar/death.png", "resources/ghostchar/death.xml", 1, false);
	//this->play("Idle");
}

//Called automatically by collision system when something collides with the player
//our job is to simply react to that collision.
 bool Player::onCollision(DisplayObject* other){
	 if(other->gameType == "platform"){
		//MyGame::collisionSystem.resolveCollision(this, other, this->position.x - oldX, this->position.y - oldY);	
		// cout<<"ydelta in: "<< this->position.y - oldY<<endl;
		// MyGame::collisionSystem->resolveCollision(this, other, this->position.x - oldX, this->position.y - oldY,
		// 	0, 0);
		//MyGame::collisionSystem->resolveCollision
		//this->collideing = true;
		//DisplayObject::onCollision(other);
		this->_yVel = 0;
		//_yAccCount= 0;
		this->standing=true;
		return false;
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
	//cout<<"yaccount num: "<<_yAccCount<<endl;
	state_combat_cooldown_counter_start++;
	//cout<<"yaccount num: "<<state_combat_cooldown_counter_start<<endl;
	// oldY = this->position.y;
	// oldX = this->position.x;
	// this->prevPos.x = oldX;
	// this->prevPos.y = oldY;

	/* Jumping */
	if (this->standing && MyGame::controls->pressJump()){
		//cout<<"jump"<<endl;
		this->_yVel = _jumpVel;
		this->standing = false;
		this->play("Jump");
		cout<<"jump"<<endl;
		jump_buffer_start = true;
		// if (this->position.y < 350 && Game::camera->position.y+this->_yVel < MyGame::currentScene->top) 
		// {
		// 	Game::camera->position.y+=this->_yVel;
		// 	cout << "Jumping cam " << endl;
		// }
	}
/* 	if(this->standing){
		jump_buffer_start = false;
		jump_buffer = 0;
	}
	if (jump_buffer_start == true){
		jump_buffer++;
	} */
	/* double jump*/
	if(this->state == "MovAblStart"){
		activestates.insert("MovAblStart");
		//cout<<"insert"<<endl;
		//state_mov_cooldown_counter++;
		//cout<<"cooldown: "<<state_cooldown_counter<<endl;
		
	}
	/** sprint**/
	if (this->state == "sprint"){
		activestates.insert("sprint");
	}
	/* High jump*/
	if (this->state == "High jump"){
		activestates.insert("High jump");
	}
	/* cool down movment ability Start timer */
	if (state_combat_cooldown_counter_start == 20){
		//cout<<"cooldown if"<<endl;
		/* movement abilities */
		if (activestates.find("MovAblStart") != activestates.end() || activestates.find("sprint") != activestates.end() || activestates.find("High jump") != activestates.end()){
			state_mov_cooldown_counter++;
			if (activestates.find("sprint") != activestates.end()){
				sprint = 4;
			}
			if(activestates.find("MovAblStart") != activestates.end()){
				cout<<"jump found"<<endl;
				cout<<standing<<" "<<MyGame::controls->pressJump()<<" "<<activated<<" "<<jump_buffer %4<<endl;
				if (!this->standing && MyGame::controls->pressJump() && activated == false) //&& jump_buffer %4 == 0){
					cout<<"double"<<endl;
					this->_yVel = _jumpVel;
					this->play("Jump");
					activated = true;
				}
			if(activestates.find("High jump") != activestates.end()){
				_yAcc = 4;
			}
				
		}
		state_combat_cooldown_counter_start = 0;
	}
	/** ghost ability */
	if(this->state == "ghost"){
		activestates.insert("ghost");
	}
	if (activestates.find("ghost") != activestates.end()){
		this->alpha = 75;
		//this-> = 200;
		
		//this->getTexture().
		activated = true;
		state_combat_cooldown_counter++;
	}
	/** shield ability */
	if(this->state == "shield"){
		activestates.insert("shield");
	}
	if (activestates.find("shield") != activestates.end()){
		SDL_SetTextureColorMod(this->getTexture(), 125,125,250);
		//this-> = 200;	
		//this->getTexture().
		activated = true;
		state_combat_cooldown_counter++;
	}
	if (MyGame::camera->position.x == MyGame::currentScene->right){
		left = true;
		right = false;
		// cout << "changed to left" << endl;
	}
	else if (MyGame::camera->position.x == MyGame::currentScene->left){
		right = true;
		left = false;
		// cout << "changed to right!" << endl;
	}
	//Movement arrow keys
	//Controls is a class we wrote that just checks the SDL Scancode values and game controller values in one check
	if(MyGame::controls->holdRight()){
		this->position.x += 4 + sprint;
		this->facingRight = true;
		if(this->standing){
			this->play("Run");
		}
		//when to move camera at start of level 
		if (right && this->position.x > 400
			&& MyGame::camera->position.x-4 + sprint >= MyGame::currentScene->right) { //windowWidth/2
			MyGame::camera->position.x-=4 + sprint;
			// cout << "first right" << endl;
		}
		else if (left && this->position.x > 400) {
			left = false; 
			right = true; 
		}
		//when to move at end of level
		else if (left && MyGame::camera->position.x-4 + sprint >= MyGame::currentScene->right
			&& this->position.x < (abs(MyGame::currentScene->right) + 400)) {
				MyGame::camera->position.x-=4 + sprint;
		} 
	}
	else if(MyGame::controls->holdLeft()){
		this->position.x -= 4 + sprint;
		this->facingRight = false;
		if(this->standing){
			this->play("Run");
		}
		//move camera at start of level 
		if (right && this->position.x > 400 && MyGame::camera->position.x + 2 + sprint <= MyGame::currentScene->left) {
			MyGame::camera->position.x+=2 + sprint;
			// cout << "first left" << endl;
		}
		else if (right && this->position.x < 400) {
			right = false; 
			left = true;
		}
		else if (left && MyGame::camera->position.x + 2 + sprint <= MyGame::currentScene->left
			&& this->position.x < (abs(MyGame::currentScene->right) + 400)) {
				MyGame::camera->position.x+=4 + sprint;
		}
	} 
	else if (this->standing){
		//this->play("Idle");
	}
	
	/* cool down combat ability timer */
	if (state_combat_cooldown_counter == 200){
		cout<<"state_combat_cooldown_counter == 200"<<endl;
		this->state = "normal";
		this->alpha = 255;
		//this->setTexture(normaltexture);
		activated = false;
		state_combat_cooldown_counter = 0;
		SDL_SetTextureColorMod(this->getTexture(), 255,255,255);
		activestates.erase("ghost");
		activestates.erase("shield");
		//cout<<"act states num: "<<activestates.size()<<endl;
	}
	
	/* cool down movment ability timer */
	if (state_mov_cooldown_counter == 2){
		cout<<"state_mov_cooldown_counter == 200"<<endl;
		this->state = "normal";
		activated = false;
		state_mov_cooldown_counter = 0;
		sprint = 0;
		_yAcc = 2;
		_yAccCount = 0;
		//cout<<"_yacc = "<<_yAcc<<endl;
		activestates.erase("MovAblStart");
		activestates.erase("sprint");
		activestates.erase("High jump");
		state_combat_cooldown_counter_start = 0;
		//cout<<"act states num: "<<activestates.size()<<endl;
	}
	//play idle animation if player is just standing still on ground
	if(this->standing && !MyGame::controls->holdLeft() && !MyGame::controls->holdRight()){
		// this->play("Idle");
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
		//cout<<"_yacc = "<<_yAcc<<endl;
		_yAccCount=0;
		this->_yVel++;
		if(this->_yVel > _maxFall) this->_yVel = _maxFall;
	}

	//}


	/* Actual falling depending on falling versus whether a jump occurred */
	this->position.y += this->_yVel;
	// if (this->position.y > 350 && !this->standing && Game::camera->position.y-this->_yVel > MyGame::currentScene->bottom) 
	// {
	// 	Game::camera->position.y-=this->_yVel;
	// 	cout << "fell cam " << endl;
	// }
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
