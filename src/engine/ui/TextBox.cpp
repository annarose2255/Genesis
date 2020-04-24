#include "TextBox.h"
#include "DisplayObject.h"
#include "Game.h"
#include <iostream>

using namespace std;

TextBox::TextBox() : Sprite() {
	this->id = "TextBox";

	// Set this way to allow white lines to show
	this->width = 799;
	this->height = 99;
	this->isUI = true;
	this->position.x = 0;
	this->position.y = 600;
	this->numBoxes = 1;

	font = TTF_OpenFont("./resources/fonts/sans.ttf", 55);

}

TextBox::TextBox(int numBoxes) : Sprite() {
	this->id = "TextBox";

	// Set this way to allow white lines to show
	this->width = 799;
	this->height = 99;
	this->isUI = true;
	this->position.x = 0;
	this->position.y = 600;
	this->numBoxes = numBoxes;

	for (int i=0; i < numBoxes; i++) {
		TextBox* tempBox = new TextBox();
		tempBox->height = this->height/numBoxes;
		tempBox->position.y = (this->height/numBoxes) * i;
		tempBox->showLines = false;
		boxes.push_back(tempBox);
		this->addChild(tempBox);
	}

	font = TTF_OpenFont("./resources/fonts/sans.ttf", 55);

}

TextBox::~TextBox(){
	if(font != NULL) TTF_CloseFont(font);
	if(surface != NULL) SDL_FreeSurface(surface);
}

void TextBox::setText(string txt) {
	this->text = txt;
	SDL_Color color = { 255, 255, 255 }; // white
	if (numBoxes==1) {
		surface = TTF_RenderText_Solid(font, text.c_str(), color);
		loadTexture(surface);
	}
	else {
		this->queueUp(txt);
		for (int i = 0; i<numBoxes; i++){
			boxes[i]->setText(textQueue[0]);
			textQueue.erase(textQueue.begin());
		}
	}
}

void TextBox::queueUp(string txt) {
	int ind = 0;
	int i = 0;
	while (true){
		ind = i;
		if(i+22 < txt.size()){
			textQueue.push_back(txt.substr(i,22));
			i += 22;
		} else {
			textQueue.push_back(txt.substr(ind));
			break;
		}
	}
}

void TextBox::continueQueue() {
	if (textQueue.size() < numBoxes) {
		for (int i = 0; i<numBoxes; i++){
			if (i < textQueue.size()) {
				boxes[i]->setText(textQueue[0]);
				textQueue.erase(textQueue.begin());
			} else {
				boxes[i]->setText(".");
			}
		}
	} else {
		for (int i = 0; i<numBoxes; i++){
			boxes[i]->setText(textQueue[0]);
			textQueue.erase(textQueue.begin());
		}
	}
}

void TextBox::update(set<SDL_Scancode> pressedKeys, set<SDL_GameControllerButton> pressedButtons, set<pair<SDL_GameControllerAxis, float>> movedAxis) {
	Sprite::update(pressedKeys, pressedButtons, movedAxis);
	if(this->visible) {
		for(SDL_Scancode key : pressedKeys) {
			switch (key) {
				case SDL_SCANCODE_RETURN:
					if (!textQueue.empty() && Game::frameCounter%20 == 0) {
						this->continueQueue();
					}
					break;
			}
		}
	}
}

void TextBox::draw(AffineTransform &at) {
	if(this->visible) {
		Sprite::draw(at);

		if ((showLines || numBoxes>1)){

			SDL_SetRenderDrawBlendMode(Game::renderer, SDL_BLENDMODE_BLEND);
			SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, this->alpha);
			// Draw a white border around the textbox
			SDL_RenderDrawLine(Game::renderer, this->position.x, this->position.y, this->position.x + this->width, this->position.y);
			SDL_RenderDrawLine(Game::renderer, this->position.x+this->width, this->position.y, this->position.x + this->width, this->position.y+this->height);
			SDL_RenderDrawLine(Game::renderer, this->position.x+this->width, this->position.y+this->height, this->position.x, this->position.y+this->height);
			SDL_RenderDrawLine(Game::renderer, this->position.x, this->position.y, this->position.x, this->position.y+this->height);
		}
	}

}