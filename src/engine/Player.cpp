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
	//normaltexture = this->getTexture();
	//SDL_Texture* b;
	//b = this->getTexture();
	//S////DL_SetTextureColorMod(b, 125,125,250);
	//shieldtexture = b;
	//this = a;
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
		if (this->position.y < 350 && MyGame::camera->position.y+this->_yVel > MyGame::currentScene->top && 
			MyGame::camera->position.y+this->_yVel < MyGame::currentScene->bottom) 
		{
			cout << "added " << MyGame::camera->position.y+this->_yVel << endl; 
			cout << "top " << MyGame::currentScene->top << endl;
			MyGame::camera->position.y+=this->_yVel;
		}
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

	//Movement arrow keys
	//Controls is a class we wrote that just checks the SDL Scancode values and game controller values in one check
	if(MyGame::controls->holdRight()){
		this->position.x += 2 + sprint;
		this->facingRight = true;
		if(this->standing){
			this->play("Run");
		}
		//if (MyGame::camera->position.x == MyGame::currentScene->right)
		//set backwards
		//check if going forward or backward through a level
		//if forward
		if (this->position.x > 400 && MyGame::camera->position.x-2 + sprint > MyGame::currentScene->right) { //windowWidth/2
			MyGame::camera->position.x-=2 + sprint;
		}
		//if backwards
		// if (this->position.x < 400 && MyGame::camera->position.x+2 > MyGame::currentScene->right){
			
		// }
	}
	else if(MyGame::controls->holdLeft()){
		this->position.x -= 2 + sprint;
		this->facingRight = false;
		if(this->standing){
			this->play("Run");
		}
		//if (MyGame::camera->position.x > MyGame::currentScene->left)
		//set forwards
		if (this->position.x > 400 && MyGame::camera->position.x + 2 + sprint < MyGame::currentScene->left) {
			MyGame::camera->position.x+=2 + sprint;
		}
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
	if (this->position.y > 350 && !this->standing && MyGame::camera->position.y-this->_yVel < MyGame::currentScene->bottom &&
		MyGame::camera->position.y-this->_yVel > MyGame::currentScene->top) 
	{
		cout << "subtracted " << MyGame::camera->position.y-this->_yVel << endl;
		cout << "bottom " << MyGame::currentScene->bottom << endl;
		MyGame::camera->position.y-=this->_yVel;
	}
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
