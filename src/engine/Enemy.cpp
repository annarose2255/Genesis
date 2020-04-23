#include "Enemy.h"
#include "DisplayObjectContainer.h"
#include "AnimatedSprite.h"
#include <cstdlib>

using namespace std;

//Here, "Sayu" is the player character
Enemy::Enemy(Player* p): AnimatedSprite("Enemy"){
	this->type = "Enemy";
	this->player = p;
	this->width = 42; this->height = 40;
	this->pivot.x = this->width/2;
	this->pivot.y = this->height/2;
    this->state = "start";
}
//Here, "Sayu" is the player character
///Enemy::Enemy(Player* sayu): AnimatedSprite("Enemy"){

void Enemy::update(set<SDL_Scancode> pressedKeys, set<SDL_GameControllerButton> pressedButtons, set<pair<SDL_GameControllerAxis, float>> movedAxis){
	Sprite::update(pressedKeys, pressedButtons, movedAxis);

	
	//enemy is dead so clean it up
	if(this->health == 0){
		this->clean = true; //scene will clean it up
	}
	//do the actual cleaning if necessary
	if(this->clean){
		this->removeThis();
		delete this;
	}

	//everything else controlled by state machine
	//state 0 = one time state to kick things off
	//state 1 = patrolling
	//state 2 = readying a charge
	//state 3 = charging
	//state 4 = post-charge movement
	//state 5 = stunned
	
	if(this->state == "start"){
		setPatrolRange();
	}
	else if(this->state == "patrol"){
		patrol();
	}
	else if(this->state == "ready charge"){
		prepareCharge();
	}
	else if(this->state == "charging"){
		// this->targX = sayu->x;
		// this->targY = sayu->y;
		charge();
	}
	else if(this->state == "post-charge movement"){
		moveToTarget();
	}
	else if(this->state == "stunned"){	
		this->rotation -= 1;
	}

	//state transitions
	if(this->state == "start"){
		this->state = "patrol";
		this->targX = std::rand()%(this->maxPatX-this->minPatX) + this->minPatX;
		this->targY = std::rand()%(this->maxPatY-this->minPatY) + this->minPatY;
        cout<<"targetx = "<<this->targX<<endl;
		this->vel = 0;
		this->maxVel = 4;
	}
	else if(this->state == "patrol"){
		//if player is close, start to prepare charge
		int dist = std::max(std::abs(this->position.x-this->player->position.x),std::abs(this->position.y-this->player->position.y));
		
		if(dist<500){
			this->state = "ready charge";
			this->vel = 0;
			this->maxVel = 12;
			this->acc = 0.5;
			this->rotVel = 0;
			this->rotAcc = 0.4;
			this->maxRotVel = 20;
		}
	}
	else if(this->state == "ready charge"){
		if(std::abs(this->rotVel - this->maxRotVel) < 0.0001){
			this->state = "charging";
			this->targX = this->player->position.x;
			this->targY = this->player->position.y;
		}
	}
	else if(this->state == "charging"){
		if(isTargetReached()){
			this->state = "post-charge movement";
			this->rotation = 0;
			this->rotVel = 0;
			this->targX = this->position.x;
			this->targY = this->position.y - 350;
		}
	}
	else if(this->state == "post-charge movement"){
		if(isTargetReached()){
			this->state = "patrol";
			this->setPatrolRange();
		}
	}
	if(this->shield == 0){
		this->state = "stunned";
	}
}

void Enemy::onMeleeStrike(){
	this->shield -= 10;
	if(this->shield < 0) this->shield = 0;
}

/* void Enemy::onEssenceStrike(Weapon* w){

	if(this->shield <= 0) this->health -= w->damage;
	if(this->health < 0) this->health = 0;
} */

void Enemy::onCollision(DisplayObject* other){
/* 	if(other->type == "Weapon"){
		if(controls::pressSpecial()) 
			onEssenceStrike((Weapon*)other);
	} */
/* 	if(other->type == "Blast"){
		if(controls::pressAttack())
			onMeleeStrike();
	} */
}

void Enemy::draw(AffineTransform &at){
	Sprite::draw(at);
	//this->drawHitbox();
}

void Enemy::save(ofstream &out){
	//Sprite::save(out);
	//TODO: ADD THIS TO SAVE ENEMY DATA
}

void Enemy::charge(){
	this->rotation += this->rotVel;
	moveToTarget();
}

void Enemy::prepareCharge(){
	this->rotVel = std::min(this->rotVel+this->rotAcc, this->maxRotVel);
	this->rotation += this->rotVel;
}

void Enemy::setPatrolRange(){
	this->minPatX = this->position.x-120;
	this->maxPatX = this->position.x+120;
	this->minPatY = this->position.y-120;
	this->maxPatY = this->position.y+120;
}

void Enemy::patrol(){
	//if close to target, set a new one
	
	if(isTargetReached() && pauseCount == 119){
		this->targX = std::rand()%(this->maxPatX-this->minPatX) + this->minPatX;
		this->targY = std::rand()%(this->maxPatY-this->minPatY) + this->minPatY;
		this->vel = 0;
		this->maxVel = 4;
		this->pauseCount = 0;
	}

	if(pauseCount < 119){
		pauseCount = (pauseCount+1) % 120;
	}
	else{
		moveToTarget();
	}
}

void Enemy::moveToTarget(){
	
	//increase velocity by accel
    cout<<"vel: "<<vel<<endl;
    this->vel = std::min(this->vel+this->acc, this->maxVel);
    cout<<"vel2: "<<vel<<endl;

	//use unit vector to determine percent that goes into x and y 
	double theta = std::atan2(std::abs(this->targY - this->position.y),std::abs(this->targX - this->position.x));
	double xComp = this->vel*std::cos(theta);
	double yComp = this->vel*std::sin(theta);
	if(this->targX - this->position.x < 0) xComp *= -1;
	if(this->targY - this->position.y < 0) yComp *= -1;

	this->position.x += xComp;
    cout<<"change x : "<<position.x<<endl;
	this->position.y += yComp;
}

bool Enemy::isTargetReached(){
	return std::abs(this->position.x-this->targX) <= 6 && std::abs(this->position.y-this->targY) <= 6;
}



