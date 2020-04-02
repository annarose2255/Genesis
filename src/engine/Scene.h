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
    
    json toJson();

<<<<<<< HEAD
    DisplayObject* makeDisplayObject(json data);
    DisplayObjectContainer* makeDisplayObjectContainer(json data);
	Layer* makeLayer(json data);
    Sprite* makeSprite(json data);
    AnimatedSprite* makeAnimatedSprite(json data);

	virtual void update(set<SDL_Scancode> pressedKeys);
=======
	virtual void update(set<SDL_Scancode> pressedKeys, ControllerInput ControllerInput);
>>>>>>> collision-detection
	virtual void draw(AffineTransform &at);

	AnimatedSprite* root;
	vector<DisplayObjectContainer*> layerList; 
	vector<DisplayObject*> objects; //in the scene
	vector<AnimatedSprite*> asList;

private:

    json parse(auto* obj); //Display Objects

};

#endif
