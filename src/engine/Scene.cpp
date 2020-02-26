#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <fstream>
// #include "DisplayObject.h"
#include "DisplayObjectContainer.h"
#include "MyGame.h"
#include "Scene.h"
#include <json.hpp>

using namespace nlohmann; 
using namespace std;

Scene::Scene(){ 

}

/* Load scene from a file */
void Scene::loadScene(string sceneFilePath){
    using json = nlohmann::json;
    json j;
    ifstream ifs(sceneFilePath);
    ifs >> j;
    
    json file; 
    int i = 0;
    for (auto file : j) {
        cout << file << endl;
        DisplayObject* temp = new DisplayObject(file["name"], file["filepath"]);
    
        temp->position.x = file["position.x"];
        temp->position.y = file["position.y"];
        temp->width = file["width"];
        temp->height = file["height"];
        temp->pivot.x = file["pivot.x"];
        temp->pivot.y = file["pivot.y"];

        sceneObjects.push_back(temp);
    }
    ifs.close();
}

void Scene::update(set<SDL_Scancode> pressedKeys) {
    DisplayObject::update(pressedKeys);
    for (int i = 0; i < sceneObjects.size(); i++) {
        sceneObjects[i]->update(pressedKeys);
    }
}

void Scene::draw(AffineTransform &at) {
    DisplayObject::draw(at);
    for (int i = 0; i < sceneObjects.size(); i++) {
        sceneObjects[i]->draw(at);
    }
}