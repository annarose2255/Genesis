#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Sprite.h"
#include "Scene.h"
#include "DevTool.h"

using namespace std;

DevTool::DevTool() : Game(800, 700) {
	instance = this;

	scene1 = new Scene(); 
	scene1->loadScene("./resources/scenes/solarsystem.json");

    scene2 = new Scene();
    scene2->loadScene("./resources/scenes/character.json");
	
    change = true;

    currentScene = scene1;
    instance->addChild(currentScene);
}

DevTool::~DevTool(){
}


void DevTool::update(set<SDL_Scancode> pressedKeys){
    
    if(pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end() && change) {
        instance->removeImmediateChild(currentScene);
        currentScene = scene2;
        instance->addChild(currentScene);
        change = !change;
    }
    else if(pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end() && !change) {
        instance->removeImmediateChild(currentScene);
        currentScene = scene1;
        instance->addChild(currentScene);
        change = !change;
    }
	Game::update(pressedKeys);
}

void DevTool::draw(AffineTransform &at){
	Game::draw(at);
}

