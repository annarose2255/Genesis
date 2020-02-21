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
using namespace std;
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
    // cout << sceneFilePath << endl;
    using json = nlohmann::json;
    json j;
    ifstream ifs(sceneFilePath);
    ifs >> j;

    if (sceneFilePath == "././resources/newsolarsystem.json") {
            // json chara = j["character"];
            // cout << j["character"] << endl;
            // Sprite* charSprite = new Sprite("character", chara["filepath"]);
	        // charSprite->position.x = chara["position.x"];
            // charSprite->position.y = chara["position.y"];
            // charSprite->width = chara["width"];
            // charSprite->height = chara["height"];
            // //charSprite->addAnimation(chara["basepath"], chara["animName"], chara["numFrames"], chara["frameRate"], chara["loop"]);
            // s.push_back(charSprite);
            // ifs.clear();
        cout<<"??"<<endl;

        json sun = j["sun"];
        root = new Sprite("sun", sun["filepath"]);
        root->position.x = sun["position.x"]; // person.name == "Rachel"
        root->position.y = sun["position.y"];
        root->width = sun["width"];
        root->height = sun["height"];
        root->pivot.x = sun["pivot.x"];
        root->pivot.y = sun["pivot.y"];
        // root->addAnimation(sun["basepath"], sun["animName"], sun["numFrames"], sun["frameRate"], sun["loop"]);

        DisplayObjectContainer* p1container = new DisplayObjectContainer();
	    DisplayObjectContainer* p2container = new DisplayObjectContainer();
        root->addChild(p1container);
        root->addChild(p2container);

        // cout<<"??"<<endl;
        json children = sun["children"];
        
        json planet1 = children["planet1"];
        Sprite* child1 = new Sprite("planet1", planet1["filepath"]);
        child1->position.x = planet1["position.x"]; // person.name == "Rachel"
        child1->position.y = planet1["position.y"];
        child1->width = planet1["width"];
        child1->height = planet1["height"];
        child1->pivot.x = planet1["pivot.x"];
        child1->pivot.y = planet1["pivot.y"];

        p1container->addChild(child1);
    //     for (auto& x : children.items())
    //  {
    //      std::cout << "key: " << x.key() << ", value: " << x.value() << '\n';
    //      json temp = j[x.key()];
    //      Sprite* child = new Sprite(x.key(), temp["filepath"]);
    //      child->position.x = 

         
    //  }

        s.push_back(root);
    } 

    if (sceneFilePath == "././resources/solarsystem.json") {
        //Sun
        json sun = j["sun"];
        root = new Sprite("sun", sun["filepath"]);
        root->position.x = sun["position.x"]; // person.name == "Rachel"
        root->position.y = sun["position.y"];
        root->width = sun["width"];
        root->height = sun["height"];
        root->pivot.x = sun["pivot.x"];
        root->pivot.y = sun["pivot.y"];
        // root->addAnimation(sun["basepath"], sun["animName"], sun["numFrames"], sun["frameRate"], sun["loop"]);

        DisplayObjectContainer* p1container = new DisplayObjectContainer();
	    DisplayObjectContainer* p2container = new DisplayObjectContainer();
        root->addChild(p1container);
        root->addChild(p2container);

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

        s.push_back(root);
        s.push_back(planet1);
        s.push_back(planet2);
        s.push_back(moon1_1);
        doc.push_back(p1container);
        doc.push_back(p2container);
        ifs.clear();
    }
    if (sceneFilePath == "././resources/character.json") {
            // json chara = j["character"];
            // cout << j["character"] << endl;
            // Sprite* charSprite = new Sprite("character", chara["filepath"]);
	        // charSprite->position.x = chara["position.x"];
            // charSprite->position.y = chara["position.y"];
            // charSprite->width = chara["width"];
            // charSprite->height = chara["height"];
            // //charSprite->addAnimation(chara["basepath"], chara["animName"], chara["numFrames"], chara["frameRate"], chara["loop"]);
            // s.push_back(charSprite);
            // ifs.clear();
        json sun = j["sun"];
        root = new Sprite("sun", sun["filepath"]);
        root->position.x = sun["position.x"]; // person.name == "Rachel"
        root->position.y = sun["position.y"];
        root->width = sun["width"];
        root->height = sun["height"];
        root->pivot.x = sun["pivot.x"];
        root->pivot.y = sun["pivot.y"];
        // root->addAnimation(sun["basepath"], sun["animName"], sun["numFrames"], sun["frameRate"], sun["loop"]);

        DisplayObjectContainer* p1container = new DisplayObjectContainer();
	    DisplayObjectContainer* p2container = new DisplayObjectContainer();
        root->addChild(p1container);
        root->addChild(p2container);

        s.push_back(root);
    } 
    ifs.close();

}

void Scene::update(set<SDL_Scancode> pressedKeys){
    DisplayObjectContainer::update(pressedKeys);
    root->update(pressedKeys);
    // for (int i = 0; i < s.size(); i++) {
    //     s[i]->update(pressedKeys);
    // }



}

void Scene::draw(AffineTransform &at){
    DisplayObjectContainer::draw(at);
    root->draw(at);
    // for (int i = 0; i < s.size(); i++) {
    //     s[i]->draw(at);
    // }
}
