#ifndef SCENE_H
#define SCENE_H

#include "DisplayObjectContainer.h"
#include "AnimatedSprite.h"
#include "Sprite.h"
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Scene : public DisplayObjectContainer{

public:
	Scene();

	/* Load scene from a file */
	void loadScene(string sceneFilePath);

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);
	vector<AnimatedSprite*> as1; 
	vector<AnimatedSprite*> as2; 
	vector<Sprite*> s; 
	vector<DisplayObjectContainer*> doc; 

private:
};

#endif
