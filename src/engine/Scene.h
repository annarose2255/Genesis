#ifndef SCENE_H
#define SCENE_H

#include "DisplayObject.h"
#include "DisplayObjectContainer.h"
#include "Sprite.h"
#include "Layer.h"
#include "AnimatedSprite.h"
#include <json.hpp>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

using json = nlohmann::json;

class Scene : public DisplayObjectContainer{

public:
	Scene();

	/* Load scene from a file */
	void loadScene(string sceneFilePath);
	void loadTileMap(string tilePath, bool isNextMap); 

    DisplayObject* makeDisplayObject(json data);
    DisplayObjectContainer* makeDisplayObjectContainer(json data);
	Layer* makeLayer(json data);
    Sprite* makeSprite(json data);
    AnimatedSprite* makeAnimatedSprite(json data);

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

	DisplayObject* getObject(int index);
	AnimatedSprite* getCharacter();
	DisplayObjectContainer* getEnemy(int index);
	void setCharacter(AnimatedSprite* chara); 
	//add get Layer method?

private:
	vector<DisplayObject*> objects; //in the scene
	vector<DisplayObjectContainer*> enemies; //in the scene
	map<int, SDL_Texture*> tilesets; //store image file of tilesets
	map<int, DisplayObject*> tileDO; //store image file of tilesets
	vector<DisplayObject*> tiles;
	AnimatedSprite* character; 
};

#endif
