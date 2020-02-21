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
<<<<<<< HEAD
    // cout << sceneFilePath << endl;
=======
    cout << sceneFilePath << endl;
>>>>>>> 58f6041ed11549ce63a02449d051d5b029d95aad
    using json = nlohmann::json;
    json j;
    ifstream ifs(sceneFilePath);
    ifs >> j;

    if (sceneFilePath == "././resources/solarsystem.json") {
        //Sun
        json sun = j["sun"];
<<<<<<< HEAD
        sunSprite = new Sprite("sun", sun["filepath"]);
=======
        AnimatedSprite* sunSprite = new AnimatedSprite("sun");
>>>>>>> 58f6041ed11549ce63a02449d051d5b029d95aad
        sunSprite->position.x = sun["position.x"]; // person.name == "Rachel"
        sunSprite->position.y = sun["position.y"];
        sunSprite->width = sun["width"];
        sunSprite->height = sun["height"];
        sunSprite->pivot.x = sun["pivot.x"];
        sunSprite->pivot.y = sun["pivot.y"];
<<<<<<< HEAD
        // sunSprite->addAnimation(sun["basepath"], sun["animName"], sun["numFrames"], sun["frameRate"], sun["loop"]);
=======
        sunSprite->addAnimation(sun["basepath"], sun["animName"], sun["numFrames"], sun["frameRate"], sun["loop"]);
>>>>>>> 58f6041ed11549ce63a02449d051d5b029d95aad

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

<<<<<<< HEAD
        s.push_back(sunSprite);
=======
        as1.push_back(sunSprite);
>>>>>>> 58f6041ed11549ce63a02449d051d5b029d95aad
        s.push_back(planet1);
        s.push_back(planet2);
        s.push_back(moon1_1);
        doc.push_back(p1container);
        doc.push_back(p2container);
        ifs.clear();
    }
    if (sceneFilePath == "././resources/character.json") {
<<<<<<< HEAD
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
        sunSprite = new Sprite("sun", sun["filepath"]);
        sunSprite->position.x = sun["position.x"]; // person.name == "Rachel"
        sunSprite->position.y = sun["position.y"];
        sunSprite->width = sun["width"];
        sunSprite->height = sun["height"];
        sunSprite->pivot.x = sun["pivot.x"];
        sunSprite->pivot.y = sun["pivot.y"];
        // sunSprite->addAnimation(sun["basepath"], sun["animName"], sun["numFrames"], sun["frameRate"], sun["loop"]);

        DisplayObjectContainer* p1container = new DisplayObjectContainer();
	    DisplayObjectContainer* p2container = new DisplayObjectContainer();
        sunSprite->addChild(p1container);
        sunSprite->addChild(p2container);

        s.push_back(sunSprite);
=======
            json chara = j["character"];
            cout << j["character"] << endl;
            Sprite* charSprite = new Sprite("character", chara["filepath"]);
	        charSprite->position.x = chara["position.x"];
            charSprite->position.y = chara["position.y"];
            charSprite->width = chara["width"];
            charSprite->height = chara["height"];
            //charSprite->addAnimation(chara["basepath"], chara["animName"], chara["numFrames"], chara["frameRate"], chara["loop"]);
            s.push_back(charSprite);
            ifs.clear();
>>>>>>> 58f6041ed11549ce63a02449d051d5b029d95aad
    } 
    ifs.close();

}

void Scene::update(set<SDL_Scancode> pressedKeys){
    DisplayObjectContainer::update(pressedKeys);
<<<<<<< HEAD
    sunSprite->update(pressedKeys);
    // for (int i = 0; i < s.size(); i++) {
    //     s[i]->update(pressedKeys);
    // }



=======
    for (int i = 0; i < as1.size(); i++) {
        as1[i]->update(pressedKeys);
    }
>>>>>>> 58f6041ed11549ce63a02449d051d5b029d95aad
}

void Scene::draw(AffineTransform &at){
    DisplayObjectContainer::draw(at);
<<<<<<< HEAD
    sunSprite->draw(at);
    // for (int i = 0; i < s.size(); i++) {
    //     s[i]->draw(at);
    // }
=======
    for (int i = 0; i < as1.size(); i++) {
        as1[i]->draw(at);
    }
>>>>>>> 58f6041ed11549ce63a02449d051d5b029d95aad
}
