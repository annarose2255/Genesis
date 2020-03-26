#ifndef SCENE_H
#define SCENE_H

#include "DisplayObject.h"
#include "DisplayObjectContainer.h"
#include "Sprite.h"
<<<<<<< HEAD
#include "Layer.h"
=======
>>>>>>> 28124d242415859506e8cf02a75402fa03d3229c
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

    DisplayObject* makeDisplayObject(json data);
    DisplayObjectContainer* makeDisplayObjectContainer(json data);
<<<<<<< HEAD
	Layer* makeLayer(json data);
=======
>>>>>>> 28124d242415859506e8cf02a75402fa03d3229c
    Sprite* makeSprite(json data);
    AnimatedSprite* makeAnimatedSprite(json data);

	virtual void update(set<SDL_Scancode> pressedKeys);
<<<<<<< HEAD
	virtual void draw(AffineTransform &at, SDL_Rect camera);

	AnimatedSprite* root;
	vector<DisplayObjectContainer*> layerList; 
	vector<DisplayObject*> objects; //in the scene
	vector<AnimatedSprite*> asList;
=======
	virtual void draw(AffineTransform &at);

>>>>>>> 28124d242415859506e8cf02a75402fa03d3229c

private:

};

#endif
