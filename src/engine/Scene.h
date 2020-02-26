#ifndef SCENE_H
#define SCENE_H

#include "DisplayObjectContainer.h"
#include "Sprite.h"
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Scene : public DisplayObject{

public:
	Scene();

	/* Load scene from a file */
	void loadScene(string sceneFilePath);
	
	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);


private:
	vector<DisplayObject*> sceneObjects;
};

#endif