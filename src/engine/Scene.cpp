#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <fstream>
#include <json.hpp>
#include "LTexture.h"
#include "MyGame.h"
#include "Scene.h"

using namespace nlohmann;
using namespace std;

Scene::Scene(){
   
}

/* Load scene from a file */
void Scene::loadScene(string sceneFilePath){
    // cout << sceneFilePath << endl;
     using json = nlohmann::json;
    json j;
    ifstream ifs(sceneFilePath);
    ifs >> j;
  
    for (int i = 0; i < j.size(); i++) {
        json file = j[i];
        LTexture* temp;
        temp->loadFromFile(file["filepath"]);
        //set name to distinguish from other LTextures 
        temp->name = file["name"];
        temp->position.x = file["position.x"];
        temp->position.y = file["position.y"];
        temp->width = file["width"];
        temp->height = file["height"];
        temp->pivot.x = file["pivot.x"];
        temp->pivot.y = file["pivot.y"];
    }
    ifs.close();
}
