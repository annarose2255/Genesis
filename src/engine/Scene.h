#ifndef SCENE_H
#define SCENE_H

#include "DisplayObjectContainer.h"
#include "DisplayObject.h"
#include "AnimatedSprite.h"
// #include "EventDispatcher.h"
#include "Sprite.h"
#include "Layer.h"
#include <string>
#include <vector>
#include <json.hpp>
#include <fstream>

using namespace std;

using json = nlohmann::json;

class Scene : public DisplayObjectContainer{

public:
	Scene();
	~Scene();
	/* Load scene from a file */
	void loadScene(string sceneFilePath);
    json toJson();
	void loadTileMap(string tilePath);

    DisplayObject* makeDisplayObject(json data);
    DisplayObjectContainer* makeDisplayObjectContainer(json data);
	Layer* makeLayer(json data);
    Sprite* makeSprite(json data);
    AnimatedSprite* makeAnimatedSprite(json data);

	virtual void update(set<SDL_Scancode> pressedKeys, ControllerInput ControllerInput);
	virtual void draw(AffineTransform &at);

	DisplayObject* getObject(int index);
	DisplayObjectContainer* getEnemy(int index);
	void addEnemy(DisplayObjectContainer* enemy);
	AnimatedSprite* getCharacter();
	void setCharacter(AnimatedSprite* chara);

private:
	map<int, SDL_Texture*> tilesets; //store image file of 
	map<string, SDL_Point> transitionPts; //store image file of tilesets
	AnimatedSprite* character;
	string sceneName;
	vector<DisplayObject*> objects; 
	vector<DisplayObjectContainer*>enemies; 

	// EventDispatcher* eDispatcher; 
    json parse(auto* obj); //Display Objects

};

#endif