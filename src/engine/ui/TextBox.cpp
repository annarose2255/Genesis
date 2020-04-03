#include "TextBox.h"
#include "DisplayObject.h"
#include "Game.h"

using namespace std;

TextBox::TextBox(int red, int green, int blue) : Sprite() {
	this->id = "TextBox";

	this->width = 800;
	this->height = 100;

	font = TTF_OpenFont("arial.ttf", 25);

}

TextBox::~TextBox(){
	if(font != NULL) TTF_CloseFont(font);
	if(surface != NULL) SDL_FreeSurface(surface);
}

void TextBox::setText(string txt) {
	this->text = txt;

	SDL_Color color = { 255, 255, 255 };
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