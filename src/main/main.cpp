#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <DisplayObject.h>
#include <iostream>
#include "MyGame.h"
#include "DevTool.h"
#include "SheetDemo.h"
#include "CollisionDemo.h"
#include "AnimatedSprite.h"
#include "rapidxml_utils.hpp"

using namespace std;
using namespace rapidxml;

int main(int argc, char ** argv)
{
  
<<<<<<< HEAD
    // SheetDemo* sheetDemo = new SheetDemo();
    // sheetDemo->start();
    // delete sheetDemo;
    // return 0;
  
/*
    // Testing rapid xml
    file<> xmlFile("./resources/quest/Gold.xml");
    xml_document<> doc;
    doc.parse<0>(xmlFile.data());
    cout << doc.first_node()->name() << endl;
    xml_node<> *node = doc.first_node("TextureAtlas");
    cout << node->first_node()->first_attribute()->next_attribute("w")->value() << endl;
*/
=======
//     SheetDemo* sheetDemo = new SheetDemo();
//     sheetDemo->start();
//     delete sheetDemo;
//     return 0;

    CollisionDemo* collisionDemo = new CollisionDemo();
    collisionDemo->start();
    delete collisionDemo;
    return 0;

// // /*
//     // Testing rapid xml
//     file<> xmlFile("./resources/quest/Gold.xml");
//     xml_document<> doc;
//     doc.parse<0>(xmlFile.data());
//     cout << doc.first_node()->name() << endl;
//     xml_node<> *node = doc.first_node("TextureAtlas");
//     cout << node->first_node()->first_attribute()->next_attribute("w")->value() << endl;
// */
>>>>>>> collision-detection

/*
    AnimatedSprite* anim = new AnimatedSprite("Gold", "./resources/quest/Gold.png", "./resources/quest/Gold.xml");
*/
	DevTool* devTool = new DevTool();
    devTool->start();

	delete devTool;
	return 0;


	// MyGame* myGame = new MyGame();
    // myGame->start();

	// delete myGame;
	// return 0;

	// QuestDemo* questDemo = new QuestDemo();
	// questDemo->start();

	// delete questDemo;
	// return 0;
}
