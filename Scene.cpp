#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <fstream>
// #include "DisplayObject.h"
#include "DisplayObjectContainer.h"
#include "MyGame.h"
#include "Scene.h"

Scene::Scene(){

}

/* Load scene from a file */
void Scene::loadScene(string sceneFilePath){
    string line;
    ifstream myfile (sceneFilePath);
    if (myfile.is_open()){
        // while ( getline (myfile,line) )
        // {
        //     // object and its x,y location, its scale, rotation,image file path, etc    
        // }

        //hard code this part
        //ex) string x = getline(myfile,line); --> x position of the character
        //etc

        myfile.close();
    }

}

virtual void Scene::update(set<SDL_Scancode> pressedKeys){

}

virtual void Scene::draw(AffineTransform &at){

}