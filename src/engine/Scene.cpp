#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <fstream>
// #include "DisplayObject.h"
#include "DisplayObjectContainer.h"
#include <json.hpp>
#include "MyGame.h"
#include "Scene.h"

using namespace nlohmann;
Scene::Scene(){

}

//vector of sprites --> while parsing have the child of the scene???

//json file
//first half: list of entity definition
//second half: hierarchy
//root --> display object container
//draw should do the add children following the hierarchy


/* Load scene from a file */
void Scene::loadScene(string sceneFilePath){

    std::ifstream in("../solarsystem.json");
    json file = json::parse(in);

    try {
        auto& array = file.at("detectlist");

        for (auto&& val: array) {
            std::cout << val << std::endl;
        }
    } catch(std::exception&) {
        std::cout << "no luck" << std::endl;
    }

    // string line;
    // ifstream myfile (sceneFilePath);
    // if (myfile.is_open()){
    //     // while ( getline (myfile,line) )
    //     // {
    //     //     // object and its x,y location, its scale, rotation,image file path, etc    
    //     // }

    //     //hard code this part
    //     //ex) string x = getline(myfile,line); --> x position of the character
    //     //etc

    //     myfile.close();
    // }

}

void Scene::update(set<SDL_Scancode> pressedKeys){
    DisplayObjectContainer::update(pressedKeys);
}

void Scene::draw(AffineTransform &at){
    DisplayObjectContainer::draw(at);
}