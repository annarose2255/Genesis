#include "HealthBar.h"
#include "Game.h"

using namespace std;

// int maxVal = 100;
// int curVal = 100;

HealthBar::HealthBar(int red, int green, int blue) : Sprite(){
	this->id = "HealthBar";

	//width and height, but can be changed
	this->width = 100;
	this->height = 10;

	//this actual filling of the bar is just a rectangle. I'm making it a child here.
	fill = new Sprite("HealthBarFill", red, green, blue);
	fill->width = this->width;
	fill->height = this->height;

	//add the fill as a child so it draws.
	this->addChild(fill);
}

//this method instalntly sets the health bar to its value (no slow movement towards its value)
void HealthBar::setInstant(int value){
	this->curVal = value;
	this->fill->width = ((double)this->curVal / (double)this->maxVal) * this->width;
}

//update the health bar every frame
void HealthBar::update(set<SDL_Scancode> pressedKeys){

	/* Move width of bar towards its value a bit*/
	//by just moving a bit, the bar well appear to increase or decrease slowly.
	int targetWidth = ((double)this->curVal / (double)this->maxVal) * this->width;
	if(!(this->fill->width == targetWidth)) {
		int sign = 1;
		if(this->fill->width > targetWidth) sign=-1;
		this->fill->width += sign*this->speed;
	}
}

void HealthBar::draw(AffineTransform &at){
	if(this->visible){
		//draw the health bar square itself
		Sprite::draw(at);

		//Reset blendmode (just in case) and alpha and color to black
		SDL_SetRenderDrawBlendMode(Game::renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, this->alpha);

		//draw a black border around the health bar.
		SDL_RenderDrawLine(Game::renderer, this->position.x, this->position.y, this->position.x + this->width, this->position.y);
		SDL_RenderDrawLine(Game::renderer, this->position.x+this->width, this->position.y, this->position.x + this->width, this->position.y+this->height);
		SDL_RenderDrawLine(Game::renderer, this->position.x+this->width, this->position.y+this->height, this->position.x, this->position.y+this->height);
		SDL_RenderDrawLine(Game::renderer, this->position.x, this->position.y, this->position.x, this->position.y+this->height);
	}

}