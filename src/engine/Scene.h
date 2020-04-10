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
struct Tile {
	SDL_Texture* texture; 
	int x; 
	int y; 
	int region_x; 
	int region_y; 
	int w; 
	int h; 
};
class Scene : public DisplayObjectContainer{

public:
	Scene();

	/* Load scene from a file */
	void loadScene(string sceneFilePath);
    json toJson();
	void loadTileMap(string tilePath);
	void drawTile(Tile tile);

    DisplayObject* makeDisplayObject(json data);
    DisplayObjectContainer* makeDisplayObjectContainer(json data);
	Layer* makeLayer(json data);
    Sprite* makeSprite(json data);
    AnimatedSprite* makeAnimatedSprite(json data);

	virtual void update(set<SDL_Scancode> pressedKeys, ControllerInput ControllerInput);
	virtual void draw(AffineTransform &at);

	DisplayObject* getObject(int index);
	AnimatedSprite* getCharacter();
	DisplayObjectContainer* getEnemy(int index);
	void setCharacter(AnimatedSprite* chara); 
	vector<DisplayObjectContainer*> enemies; //in the scene
	vector<DisplayObject*> objects; //in the scene
	//add get Layer method?

private:
	map<int, SDL_Texture*> tilesets; //store image file of 
	map<int, string> tilepaths; //store image file of tilesets
	AnimatedSprite* character;
	vector<Tile> tiles; 
    json parse(auto* obj); //Display Objects

};

#endif