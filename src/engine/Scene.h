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
#include "Player.h"
#include "Enemy.h"

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
	Player* makePlayer(json data);

	virtual void update(set<SDL_Scancode> pressedKeys, set<SDL_GameControllerButton> pressedButtons, set<pair<SDL_GameControllerAxis, float>> movedAxis);
	virtual void draw(AffineTransform &at);

	DisplayObject* getObject();
	DisplayObject* getEnemy();
	void setEnemy(DisplayObject* enemy);
	// void addEnemy(DisplayObject* enemy);
	AnimatedSprite* getCharacter();
	Player* getPlayer();
	void setPlayer(Player* chara);
	map<int, SDL_Point> charStart; //where character should spawn in this scene
	map<int, SDL_Point> charEnd;
	int top, left, bottom, right;
	int getSceneNum(); 
	bool isBattle; 
	vector<pair<string, DisplayObject*>> enemies;
	vector<pair<string, DisplayObject*>> objects;
	vector<pair<string, DisplayObject*>> getEnemies();
	vector<Enemy*> RealEnemies;
	//void setRealEnemies(vector<Enemy*> e);
	
private:
	map<int, SDL_Texture*> tilesets; //store texture of tilesets
	map<string, SDL_Point> transitionPts;  
	AnimatedSprite* character;
	Player* player;

	bool fromTileMap;
	int sceneNum; //tells us what room we're loading 
	// vector<DisplayObject*>enemies;
	DisplayObject* curEnemy; 
	DisplayObject* curObj; 
	// bool fromTileMap;

	// EventDispatcher* eDispatcher; 
    json parse(auto* obj); //Display Objects

};

#endif