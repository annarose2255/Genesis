#ifndef SCENE_H
#define SCENE_H

#include "LTexture.h"
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Scene {

public:
	Scene();

	/* Load scene from a file */
	void loadScene(string sceneFilePath);

private:
};

#endif
