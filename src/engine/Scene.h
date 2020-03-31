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
	void loadTileMap(string tilePath); 

    DisplayObject* makeDisplayObject(json data);
    DisplayObjectContainer* makeDisplayObjectContainer(json data);
	Layer* makeLayer(json data);
    Sprite* makeSprite(json data);
    AnimatedSprite* makeAnimatedSprite(json data);

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

	AnimatedSprite* root;
	vector<DisplayObjectContainer*> layerList; 
	vector<DisplayObject*> objects; //in the scene
	vector<AnimatedSprite*> asList;
	vector<pair<int, string>> tilesets; //store image file of tilesets
	map<int, SDL_Point> tsize; //store image file of tilesets	
	// vector<pair<int, SDL_Point>> tsize; //store size of tilesets 
	vector<DisplayObject*> tiles;
private:

};

#endif
