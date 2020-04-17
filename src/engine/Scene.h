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

	virtual void update(set<SDL_Scancode> pressedKeys, set<SDL_GameControllerButton> pressedButtons, set<pair<SDL_GameControllerAxis, float>> movedAxis);
	virtual void draw(AffineTransform &at);

	DisplayObject* getObject(int index);
	DisplayObject* getEnemy();
	void setEnemy(DisplayObject* enemy);
	// void addEnemy(DisplayObject* enemy);
	AnimatedSprite* getCharacter();
	void setCharacter(AnimatedSprite* chara);
	map<int, SDL_Point> charStart; //where character should spawn in this scene
	map<int, SDL_Point> charEnd;
	int top, left, bottom, right;
	int getSceneNum(); 
	bool isBattle; 
	vector<DisplayObject*>enemies;
	vector<DisplayObject*>objects;
	
private:
	map<int, SDL_Texture*> tilesets; //store texture of tilesets
	map<string, SDL_Point> transitionPts;  
	AnimatedSprite* character;
	int sceneNum; //tells us what room we're loading 
	// vector<DisplayObject*>enemies;
	DisplayObject* curEnemy; 
	// bool fromTileMap;

	// EventDispatcher* eDispatcher; 
    json parse(auto* obj); //Display Objects

};

#endif