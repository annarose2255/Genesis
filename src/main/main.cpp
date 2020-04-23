#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <DisplayObject.h>
#include <iostream>
#include "MyGame.h"
#include "DevTool.h"
#include "SheetDemo.h"
#include "QuestDemo.h"
#include "CollisionDemo.h"
#include "AnimatedSprite.h"
#include "rapidxml_utils.hpp"

using namespace std;
using namespace rapidxml;

static void show_usage(std::string name)
{
	std::cerr << "Usage: " << name << " <option(s)> SOURCES\n"
			<< "Options:\n"
			<< "\t<no flags>\t\tStarts Game\n"
			<< "\t-h,--help\t\tShow this help message\n"
			<< "\t-d\t\t\tStarts Devtool\n"
			<< "\t-c\t\t\tStarts Collision Demo\n"
			<< "\t-q\t\t\tStarts Quest Demo\n"
			<< "\t-s\t\t\tStarts Sheet Demo\n"
			<< std::endl;
}

int main(int argc, char ** argv)
{
	// takes one command line argument
	if (argc == 2){
		if ( string(argv[1]) == "-h" || string(argv[1]) == "--help" ){
			show_usage(argv[0]);
		}
		else if ( string(argv[1]) == "-c" ){
			cout << "Starting Collision Demo..." << endl;
			CollisionDemo* collisionDemo = new CollisionDemo();
			collisionDemo->start();
			delete collisionDemo;
		}
		else if (string(argv[1]) == "-d"){
			cout << "Starting DevTool..." << endl;
			DevTool* devTool = new DevTool();
			devTool->start();
			delete devTool;
		}
		else if (string(argv[1]) == "-q"){
			cout << "Starting Sheet Demo..." << endl;
			SheetDemo* sheetDemo = new SheetDemo();
			sheetDemo->start();
			delete sheetDemo;
		} 
		else if (string(argv[1]) == "-s"){
			cout << "Starting Sheet Demo..." << endl;
			SheetDemo* sheetDemo = new SheetDemo();
			sheetDemo->start();
			delete sheetDemo;
		}
		else {
			std::cerr << "Invalid flag: " << argv[1] << "\n";
			show_usage(argv[0]);
		}
	} else if (argc == 1) {
		cout << "Starting MyGame..." << endl;
		MyGame* myGame = new MyGame();
		myGame->start();
		delete myGame;
	} else {
		std::cerr << "Invalid arguments: This program only takes one argument\n";
		show_usage(argv[0]);
	}
	return 0;
}
