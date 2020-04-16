#include "DisplayObject.h"
// #include "EventDispatcher.h"
// #include "Event.h"
// #include "DisplayObjectEvent.h"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Game.h"
#include "MyGame.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include "Player.h"

#define PI 3.14159265

DisplayObject::DisplayObject(){
	image = NULL;
	texture = NULL;
	curTexture = NULL;
	pos2.x = position.x; 
	pos2.y = position.y;
	 
	// cam = new Camera();
	this->setScrollSpeed(1.0);
	// DisplayObjectEvent* e = new DisplayObjectEvent(DO_ADDED_EVENT, EventDispatcher::getInstance(), this);
    // EventDispatcher::getInstance()->dispatchEvent(e);

}

DisplayObject::DisplayObject(string id, string filepath){
	this->id = id;
	this->imgPath = filepath;
	loadTexture(filepath);
	this->setScrollSpeed(1.0);
	// DisplayObjectEvent* e = new DisplayObjectEvent(DO_ADDED_EVENT, EventDispatcher::getInstance(), this);
    // EventDispatcher::getInstance()->dispatchEvent(e);
}

DisplayObject::DisplayObject(string id, int red, int green, int blue){
	isRGB = true;
	this->id = id;

	this->red = red;
	this->blue = blue;
	this->green = green;

	this->loadRGBTexture(red, green, blue);
	this->setScrollSpeed(1.0);
}

DisplayObject::~DisplayObject(){
	//TODO: Get this freeing working
	if(image != NULL) SDL_FreeSurface(image);
	if(texture != NULL) SDL_DestroyTexture(texture);	
}

void DisplayObject::loadTexture(SDL_Surface* srf){
	texture = SDL_CreateTextureFromSurface(Game::renderer, srf);
	setTexture(texture);
}

void DisplayObject::loadTexture(string filepath){
	image = IMG_Load(filepath.c_str());
	hitbox.width = image->w;
	hitbox.height = image->h;
	texture = SDL_CreateTextureFromSurface(Game::renderer, image);
	setTexture(texture);
}

void DisplayObject::loadRGBTexture(int red, int green, int blue){
	image = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0x000000ff);
	hitbox.width = image->w;
	hitbox.height = image->h;
	SDL_FillRect(image, NULL, SDL_MapRGB(image->format, red, green, blue));
	texture = SDL_CreateTextureFromSurface(Game::renderer, image);
	SDL_SetTextureBlendMode( texture, SDL_BLENDMODE_BLEND );
	setTexture(texture);
}

void DisplayObject::setTexture(SDL_Texture* t){
	this->curTexture = t;
}

void DisplayObject::update(set<SDL_Scancode> pressedKeys, set<SDL_GameControllerButton> pressedButtons, set<pair<SDL_GameControllerAxis, float>> movedAxis){
	
}

void DisplayObject::setScrollSpeed(double speed) {
	scrollSpeed = speed;
}
SDL_Texture* DisplayObject::getTexture(){
	return this->texture;
}
void DisplayObject::draw(AffineTransform &at){
	applyTransformations(at);
	// cout << "Drawing " << id << endl;

	if(curTexture != NULL && visible) {
		SDL_Point origin = at.transformPoint(0, 0);
		SDL_Point upperRight = at.transformPoint(width, 0);
		SDL_Point lowerRight = at.transformPoint(width, height);
		SDL_Point corner = {0, 0};

		int w = (int)distance(origin, upperRight);
		int h = (int)distance(upperRight, lowerRight);

		pos2.x = origin.x; 
		pos2.y = origin.y;

		SDL_Rect dstrect = { origin.x, origin.y, w, h }; //added this back
		// cout << "camPerspective: " << camPerspective << endl;
		if (&Game::camera != NULL && camPerspective) {
			// cout << "Camera " << Game::camera->camera.x << endl;
			dstrect.x = (int) (pos2.x - Game::camera->camera.x) * scrollSpeed; 
			dstrect.y = (int) (pos2.y - Game::camera->camera.y) * scrollSpeed; 
			if (tile) {
				// cout << "srcrect x " << srcrect.x << endl;
				// cout << "srcrect y " << srcrect.y << endl;
				// cout << "srcrect w " << srcrect.w << endl;
				// cout << "srcrect h " << srcrect.h << endl;
				dstrect.w = srcrect.w; 
				dstrect.h = srcrect.h;
			}
			else {
				dstrect.w = w; 
				dstrect.h = h;
			}
		}

		//dstrect = { origin.x, origin.y, w, h };
		
		SDL_RendererFlip flip;
		if (facingRight) {
			flip = SDL_FLIP_NONE;
		}
		else {
			flip = SDL_FLIP_HORIZONTAL;
		}
		
		SDL_SetTextureAlphaMod(curTexture, alpha);
		if (isSheet || tile) { 
            SDL_RenderCopyEx(Game::renderer, curTexture, &srcrect, &dstrect, calculateRotation(origin, upperRight), &corner, flip);	
        } else {
            SDL_RenderCopyEx(Game::renderer, curTexture, NULL, &dstrect, calculateRotation(origin, upperRight), &corner, flip);	
        }
		drawHitbox();
	}

	reverseTransformations(at);
	
}
//checks type of collision and resolves it accordingly
void DisplayObject::onCollision(DisplayObject* other){
	cout << "inside onCollision!" << endl;
	//if (this->gameType == "character"){
		//Player::this->onCollision(other);
	//}
	if (other->gameType == "platform") {
		// cout << "collided with a platform!" << endl;
		cout<<"position y check: "<<this->position.y<<endl;
		if (MyGame::collisionSystem->collidesWith(this, other) == true){
			MyGame::collisionSystem->resolveCollision(this, other, this->position.x - this->prevPos.x, this->position.y - this->prevPos.y,
			0, 0);
		}
		
	}
}
void DisplayObject::applyTransformations(AffineTransform &at) {
	at.translate(position.x, position.y);
	at.rotate(rotation);
	at.scale(scaleX, scaleY);
	at.translate(-pivot.x, -pivot.y);
}

void DisplayObject::reverseTransformations(AffineTransform &at) {
	at.translate(pivot.x, pivot.y);
	at.scale(1.0/scaleX, 1.0/scaleY);
	at.rotate(-rotation);
	at.translate(-position.x, -position.y);
}

int DisplayObject::getWidth() {
	return this->image->w;
}

int DisplayObject::getHeight() {
	return this->image->h;
}

double DisplayObject::distance(SDL_Point &p1, SDL_Point &p2) {
	return sqrt(((p2.y - p1.y)*(p2.y - p1.y)) + ((p2.x - p1.x)*(p2.x - p1.x)));
}

double DisplayObject::calculateRotation(SDL_Point &origin, SDL_Point &p) {
	double y = p.y - origin.y;
	double x = p.x - origin.x;
	return (atan2(y, x) * 180 / PI);
}

AffineTransform *DisplayObject::globalTransform() {
	AffineTransform *gt = new AffineTransform();
	if (parent != NULL){
		gt = this->parent->globalTransform();
		// undo pivot transformations
		// gt->translate(this->parent->pivot.x, this->parent->pivot.y);
	}
	this->applyTransformations(*gt);
	return gt;
}

HitboxPoints DisplayObject::getHitboxPts() {
	AffineTransform gt = *this->globalTransform();
	HitboxPoints pts;
	// width and height are hardcoded to 100 for some reason
	this->hitbox.width = width;
	this->hitbox.height = height;
	pts.topLeft = gt.transformPoint(this->hitbox.origin.x, this->hitbox.origin.y);
	pts.topRight = gt.transformPoint(this->hitbox.origin.x + this->hitbox.width, this->hitbox.origin.y);
	pts.bottomLeft = gt.transformPoint(this->hitbox.origin.x, this->hitbox.origin.y + this->hitbox.height);
	pts.bottomRight = gt.transformPoint(this->hitbox.origin.x + this->hitbox.width, this->hitbox.origin.y + this->hitbox.height);
	return pts;
}

// Line** DisplayObject::getHitboxLines() {
// 	Line* lines = new Line[4];
// 	HitboxPoints pts = this->getHitboxPts();
// 	Line* l1 = new Line();
// 	Line* l2 = new Line();
// 	Line* l3 = new Line();
// 	Line* l4 = new Line();
// 	*l1 = {pts.topLeft, pts.topRight};
// 	*l2 = {pts.topRight, pts.bottomRight};
// 	*l3 = {pts.bottomLeft, pts.bottomRight};
// 	*l4 = {pts.topLeft, pts.bottomLeft};

// }

void DisplayObject::setHitbox(SDL_Point origin, int width, int height) {
	this->hitbox.origin = origin;
	this->hitbox.width = width;
	this->hitbox.height = height;
}

void DisplayObject::drawHitbox(){
	// set draw color to white
    SDL_SetRenderDrawColor(Game::renderer, 102, 255, 0, SDL_ALPHA_OPAQUE);
    HitboxPoints pts = this->getHitboxPts();
    SDL_RenderDrawLine(Game::renderer, pts.topLeft.x, pts.topLeft.y, pts.topRight.x, pts.topRight.y);
    SDL_RenderDrawLine(Game::renderer, pts.topRight.x, pts.topRight.y, pts.bottomRight.x, pts.bottomRight.y);
	SDL_RenderDrawLine(Game::renderer, pts.bottomLeft.x, pts.bottomLeft.y, pts.bottomRight.x, pts.bottomRight.y);
	SDL_RenderDrawLine(Game::renderer, pts.topLeft.x, pts.topLeft.y, pts.bottomLeft.x, pts.bottomLeft.y);
	// set back to black
	SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
}