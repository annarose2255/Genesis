#include "TextBox.h"
#include "DisplayObject.h"
#include "Game.h"
#include <iostream>

using namespace std;

TextBox::TextBox() : Sprite() {
	this->id = "TextBox";

	this->width = 800;
	this->height = 100;

	this->position.x = 0;
	this->position.y = 600;

	// // As wide as the screen
	// this->width = Game::windowWidth;
	// this->height = 100;

	// // Set on the bottom of the screen
	// this->position.x = 0;
	// this->position.y = Game::windowHeight - 100;

	font = TTF_OpenFont("./resources/fonts/sans.ttf", 55);

}

TextBox::~TextBox(){
	if(font != NULL) TTF_CloseFont(font);
	if(surface != NULL) SDL_FreeSurface(surface);
}

void TextBox::setText(string txt) {
	this->text = txt;

	SDL_Color color = { 255, 255, 255 }; // white
	surface = TTF_RenderText_Solid(font, text.c_str(), color);
	loadTexture(surface);

}

void TextBox::update(set<SDL_Scancode> pressedKeys) {

}

void TextBox::draw(AffineTransform &at) {
	if(this->visible) {
		Sprite::draw(at);

		SDL_SetRenderDrawBlendMode(Game::renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, this->alpha);

		// Draw a white border around the textbox
		SDL_RenderDrawLine(Game::renderer, this->position.x, this->position.y, this->position.x + this->width, this->position.y);
		SDL_RenderDrawLine(Game::renderer, this->position.x+this->width, this->position.y, this->position.x + this->width, this->position.y+this->height);
		SDL_RenderDrawLine(Game::renderer, this->position.x+this->width, this->position.y+this->height, this->position.x, this->position.y+this->height);
		SDL_RenderDrawLine(Game::renderer, this->position.x, this->position.y, this->position.x, this->position.y+this->height);


	}

}