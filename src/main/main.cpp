#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <DisplayObject.h>
#include <iostream>
#include "MyGame.h"
#include "QuestDemo.h"
#include "DevTool.h"

using namespace std;

int main(int argc, char ** argv)
{
	// DevTool* devTool = new DevTool();
    // devTool->start();

	// delete devTool;
	// return 0;
	// MyGame* myGame = new MyGame();
    // myGame->start();

	// delete myGame;
	// return 0;

	QuestDemo* questDemo = new QuestDemo();
	questDemo->start();

	delete questDemo;
	return 0;
}
