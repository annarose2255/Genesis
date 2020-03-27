#include "DisplayObject.h"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Game.h"
#include <iostream>
#include <algorithm>
#include <cmath>

#define PI 3.14159265

DisplayObject::DisplayObject(){
	image = NULL;
	texture = NULL;
	curTexture = NULL;
}

DisplayObject::DisplayObject(string id, string filepath){
	this->id = id;
	this->imgPath = filepath;
	loadTexture(filepath);
}

DisplayObject::DisplayObject(string id, int red, int green, int blue){
	isRGB = true;
	this->id = id;

	this->red = red;
	this->blue = blue;
	this->green = green;

	this->loadRGBTexture(red, green, blue);
}

DisplayObject::~DisplayObject(){
	//TODO: Get this freeing working
	if(image != NULL) SDL_FreeSurface(image);
	if(texture != NULL) SDL_DestroyTexture(texture);	
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

void DisplayObject::update(set<SDL_Scancode> pressedKeys, ControllerInput controllerInput){
	
}

void DisplayObject::draw(AffineTransform &at){
	applyTransformations(at);
	
	if(curTexture != NULL && visible) {
		SDL_Point origin = at.transformPoint(0, 0);
		SDL_Point upperRight = at.transformPoint(width, 0);
		SDL_Point lowerRight = at.transformPoint(width, height);
		SDL_Point corner = {0, 0};

		int w = (int)distance(origin, upperRight);
		int h = (int)distance(upperRight, lowerRight);

		SDL_Rect dstrect = { origin.x, origin.y, w, h };

		SDL_RendererFlip flip;
		if (facingRight) {
			flip = SDL_FLIP_NONE;
		}
		else {
			flip = SDL_FLIP_HORIZONTAL;
		}
		
		SDL_SetTextureAlphaMod(curTexture, alpha);
		if (isSheet) { 
            SDL_RenderCopyEx(Game::renderer, curTexture, &srcrect, &dstrect, calculateRotation(origin, upperRight), &corner, flip);	
        } else {
            SDL_RenderCopyEx(Game::renderer, curTexture, NULL, &dstrect, calculateRotation(origin, upperRight), &corner, flip);	
        }
		cout << "drawing hitbox" << endl;
		drawHitbox();
	}

	reverseTransformations(at);
	
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

AffineTransform DisplayObject::globalTransform() {
	cout << "GT" << endl;
	AffineTransform gt;
	// if (this->parent != NULL){
	// 	cout << "have parent" << endl;
	// 	gt = this->parent->globalTransform();
	// 	// undo pivot transformations
	// }
	this->applyTransformations(gt);
	// cout << "returning" << endl;
	return gt;
}

DisplayObject::HitboxPoints DisplayObject::getHitbox() {
	cout << "getting hitbox" << endl;
	AffineTransform gt = this->globalTransform();
	HitboxPoints pts;
	pts.topLeft = gt.transformPoint(this->hitbox.origin.x, this->hitbox.origin.y);
	pts.topLeft = gt.transformPoint(this->hitbox.origin.x + this->hitbox.width, this->hitbox.origin.y);
	pts.bottomLeft = gt.transformPoint(this->hitbox.origin.x, this->hitbox.origin.y + this->hitbox.height);
	pts.bottomRight = gt.transformPoint(this->hitbox.origin.x + this->hitbox.width, this->hitbox.origin.y + this->hitbox.height);
	cout << pts.topLeft.x << " " << pts.topLeft.y << endl;
	return pts;
}

void DisplayObject::drawHitbox(){
    SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    HitboxPoints pts = this->getHitbox();
    SDL_RenderDrawLine(Game::renderer, pts.topLeft.x, pts.topLeft.y, pts.topRight.x, pts.topRight.y);
    SDL_RenderDrawLine(Game::renderer, pts.topRight.x, pts.topRight.y, pts.bottomRight.x, pts.bottomRight.y);
	SDL_RenderDrawLine(Game::renderer, pts.bottomLeft.x, pts.bottomLeft.y, pts.bottomRight.x, pts.bottomRight.y);
	SDL_RenderDrawLine(Game::renderer, pts.topLeft.x, pts.topLeft.y, pts.bottomLeft.x, pts.bottomLeft.y);
}