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
	pos2.x = position.x; 
	pos2.y = position.y;
	// cam = new Camera();
	this->setScrollSpeed(1.0);
}

DisplayObject::DisplayObject(string id, string filepath){
	this->id = id;
	this->imgPath = filepath;
	loadTexture(filepath);
	this->setScrollSpeed(1.0);
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

void DisplayObject::loadTexture(string filepath){
	image = IMG_Load(filepath.c_str());
	texture = SDL_CreateTextureFromSurface(Game::renderer, image);
	setTexture(texture);
}

void DisplayObject::loadRGBTexture(int red, int green, int blue){
	image = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0x000000ff);
	SDL_FillRect(image, NULL, SDL_MapRGB(image->format, red, green, blue));
	texture = SDL_CreateTextureFromSurface(Game::renderer, image);
	SDL_SetTextureBlendMode( texture, SDL_BLENDMODE_BLEND );
	setTexture(texture);
}

void DisplayObject::setTexture(SDL_Texture* t){
	this->curTexture = t;
}

void DisplayObject::update(set<SDL_Scancode> pressedKeys){

}
void DisplayObject::setScrollSpeed(double speed) {
	scrollSpeed = speed;
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
			if ((srcrect.x != 0 && srcrect.w < 1000) && (srcrect.y != 0 && srcrect.h < 1000)) {
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
		if (isSheet || (srcrect.x != 0 && srcrect.w < 1000) && (srcrect.y != 0 && srcrect.h < 1000)) { 
            SDL_RenderCopyEx(Game::renderer, curTexture, &srcrect, &dstrect, calculateRotation(origin, upperRight), &corner, flip);	
        } else {
            SDL_RenderCopyEx(Game::renderer, curTexture, NULL, &dstrect, calculateRotation(origin, upperRight), &corner, flip);	
        }
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
