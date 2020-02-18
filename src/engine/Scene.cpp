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
    this->type = "Scene";
}

//vector of sprites --> while parsing have the child of the scene???

//json file
//first half: list of entity definition
//second half: hierarchy
//root --> display object container
//draw should do the add children following the hierarchy


/* Load scene from a file */
void Scene::loadScene(string sceneFilePath){
    using json = nlohmann::json;
    json j;
    ifstream ifs(sceneFilePath);
    ifs >> j;
    //cout << j;
    if (sceneFilePath == "solarsystem.json") {
        //Sun
        json sun = j["sun"];
        AnimatedSprite* sunSprite = new AnimatedSprite("sun");
        sunSprite->position.x = sun["position.x"]; // person.name == "Rachel"
        sunSprite->position.y = sun["position.y"];
        sunSprite->width = sun["width"];
        sunSprite->height = sun["height"];
        sunSprite->pivot.x = sun["pivot.x"];
        sunSprite->pivot.y = sun["pivot.y"];
        sunSprite->addAnimation(sun["basepath"], sun["animName"], sun["numFrames"], sun["frameRate"], sun["loop"]);

        DisplayObjectContainer* p1container = new DisplayObjectContainer();
	    DisplayObjectContainer* p2container = new DisplayObjectContainer();
        sunSprite->addChild(p1container);
        sunSprite->addChild(p2container);

        //planet 1
        json p1 = j["planet1"];
        Sprite* planet1 = new Sprite("planet1", p1["filepath"]);
	    planet1->position.x = p1["position.x"];
        planet1->position.y = p1["position.y"];
        planet1->width = p1["width"];
        planet1->height = p1["height"];
        planet1->pivot.x = p1["pivot.x"];
        planet1->pivot.y = p1["pivot.y"];
        p1container->addChild(planet1);

        //planet 2
        json p2 = j["planet2"];
        Sprite* planet2 = new Sprite("planet2", p2["filepath"]);
	    planet2->position.x = p2["position.x"];
        planet2->position.y = p2["position.y"];
        planet2->width = p2["width"];
        planet2->height = p2["height"];
        planet2->pivot.x = p2["pivot.x"];
        planet2->pivot.y = p2["pivot.y"];
        p2container->addChild(planet2);

        //moon 1
        json m1 = j["moon1_1"];
        Sprite* moon1_1 = new Sprite("moon1_1", m1["filepath"]);
	    moon1_1->position.x = m1["position.x"];
        moon1_1->position.y = m1["position.y"];
        moon1_1->width = m1["width"];
        moon1_1->height = m1["height"];
        planet1->addChild(moon1_1);

        as.push_back(sunSprite);
        s.push_back(planet1);
        s.push_back(planet2);
        s.push_back(moon1_1);
        doc.push_back(p1container);
        doc.push_back(p2container);
    }
    ifs.close();

    // std::ifstream in("../solarsystem.json");
    // json file = json::parse(in);

    // try {
    //     auto& array = file.at("detectlist");

    //     for (auto&& val: array) {
    //         std::cout << val << std::endl;
    //     }
    // } catch(std::exception&) {
    //     std::cout << "no luck" << std::endl;
    // }

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
    for (int i = 0; i < as.size(); i++) {
        as[i]->update(pressedKeys);
    }
}

void Scene::draw(AffineTransform &at){
    DisplayObjectContainer::draw(at);
    for (int i = 0; i < as.size(); i++) {
        as[i]->draw(at);
    }
}
