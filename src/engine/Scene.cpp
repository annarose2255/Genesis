#include "Scene.h"
#include <iostream>
#include <fstream>

Scene::Scene() : DisplayObjectContainer() {
    this->type = "Scene";
}

void Scene::loadScene(string sceneFilePath) {
    json j;
    ifstream ifs(sceneFilePath);
    ifs >> j;

    this->id = j["id"]["name"];
    
    for(auto& [key, value] : j.items()) {
        json data = value;
        if(data["type"] == "DisplayObject") { // This is probably not needed?
            DisplayObject* newDO = makeDisplayObjectContainer(data);
            this->addChild(newDO);
        }
        if(data["type"] == "DisplayObjectContainer") {
            DisplayObjectContainer* newDOC = makeDisplayObjectContainer(data);
            this->addChild(newDOC);
        }
        if(data["type"] == "Sprite") {
            Sprite* newS = makeSprite(data);
            this->addChild(newS);
        }
        if(data["type"] == "AnimatedSprite") {
            AnimatedSprite* newAS = makeAnimatedSprite(data);   
            this->addChild(newAS);
        }
    }
}

json Scene::toJson() {
    json j;
    json childs;

    for(auto* entity : this->children) {
        json temp = parse(entity);
        childs.push_back(json::object_t::value_type(entity->id, temp));
    }

    // Setting name of scene
    j = {
        {"id", {"name", this->id} }, 
    };
    
    j += childs;
    return j;
}

/*
This turns a DisplayObj, Sprite, etc. pointer into a json
*/
json Scene::parse(auto* obj) {
    json j;
    j = {
        {"type", obj->type},
        {"id", obj->id},
        {"visible", obj->visible},
        {"position.x", obj->position.x},
        {"position.y", obj->position.y},
        {"width", obj->width},
        {"height", obj->height},
        {"pivot.x", obj->pivot.x},
        {"pivot.y", obj->pivot.y},
        {"scaleX", obj->scaleX},
        {"scaleY", obj->scaleY},
        {"rotation", obj->rotation},
        {"alpha", obj->alpha},
        {"facingRight", obj->facingRight}
    };

    // Having Trouble Converting...
/*
    // Animations
    if(obj->type == "AnimatedSprite") {
        json anim;
        for(int i = 0; i < obj->animationNames.size; i++) {
            json tempJson;
            Animation* tempAni = obj->getAnimation(obj->animationNames[i]);
            
            tempJson = {
                {"filepath", tempAni->filepath},
                {"name", tempAni->animName},
                {"frames", tempAni->numFrames},
                {"rate", tempAni->frameRate},
                {"loop", tempAni->loop}
            };
            
            anim += json::object_t::value_type(to_string(i), tempJson);
        }
        j += json::object_t::value_type("animations", anim);
    }
    else {
        j += json::object_t::value_type("filepath", obj->imgPath); 
    }

    // Children
    if(obj->type != "DisplayObject"){
        json childs;
        for(auto* child : obj->children) {
            json temp = parse(child);
            childs += json::object_t::value_type(temp["id"], temp);
        }
        j += json::object_t::value_type("children", childs);
    }
*/

    return j;
}

DisplayObject* Scene::makeDisplayObject(json data) {
    
    DisplayObject* newDO = new DisplayObject(data["id"], data["filepath"]);
    newDO->visible = data["visible"];
    newDO->position.x = data["position.x"];
    newDO->position.y = data["position.y"];
    newDO->width = data["width"];
    newDO->height = data["height"];
    newDO->pivot.x = data["pivot.x"];
    newDO->pivot.y = data["pivot.y"];
    newDO->scaleX = data["scaleX"];
    newDO->scaleY = data["scaleY"];
    newDO->rotation = data["rotation"];
    newDO->alpha = data["alpha"];
    newDO->facingRight = data["facingRight"];
    
    return newDO;
}

DisplayObjectContainer* Scene::makeDisplayObjectContainer(json data) {
    DisplayObjectContainer* newDOC = new DisplayObjectContainer();
    newDOC->id = data["id"];
    newDOC->visible = data["visible"];
    newDOC->position.x = data["position.x"];
    newDOC->position.y = data["position.y"];
    newDOC->width = data["width"];
    newDOC->height = data["height"];
    newDOC->pivot.x = data["pivot.x"];
    newDOC->pivot.y = data["pivot.y"];
    newDOC->scaleX = data["scaleX"];
    newDOC->scaleY = data["scaleY"];
    newDOC->rotation = data["rotation"];
    newDOC->alpha = data["alpha"];
    newDOC->facingRight = data["facingRight"];
    if(data["filepath"] != "") {
        newDOC->imgPath = data["filepath"];
        newDOC->loadTexture(data["filepath"]);
    }

    // Children
    for(auto& [key, value] : data["children"].items()) {
        json childData = value;
        if(childData["type"] == "DisplayObject") {
            DisplayObject* newDO = makeDisplayObject(childData);
            newDOC->addChild(newDO);
        }
        if(childData["type"] == "DisplayObjectContainer") {
            DisplayObjectContainer* newDOC2 = makeDisplayObjectContainer(childData);
            newDOC->addChild(newDOC2);
        }
        if(childData["type"] == "Sprite") {
            Sprite* newS = makeSprite(childData);
            newDOC->addChild(newS);
        }
        if(childData["type"] == "AnimatedSprite") {
            AnimatedSprite* newAS = makeAnimatedSprite(childData);
            newDOC->addChild(newAS);
        }
    }
    return newDOC;
}

Sprite* Scene::makeSprite(json data) {
    Sprite* newS = new Sprite(data["id"], data["filepath"]);
    newS->visible = data["visible"];
    newS->position.x = data["position.x"];
    newS->position.y = data["position.y"];
    newS->width = data["width"];
    newS->height = data["height"];
    newS->pivot.x = data["pivot.x"];
    newS->pivot.y = data["pivot.y"];
    newS->scaleX = data["scaleX"];
    newS->scaleY = data["scaleY"];
    newS->rotation = data["rotation"];
    newS->alpha = data["alpha"];
    newS->facingRight = data["facingRight"];
    //newS->imgPath = data["filepath"];
            
    // Children
    for(auto& [key, value] : data["children"].items()) {
        json childData = value;
        if(childData["type"] == "DisplayObject") {
            DisplayObject* newDO = makeDisplayObject(childData);
            newS->addChild(newDO);
        }
        if(childData["type"] == "DisplayObjectContainer") {
            DisplayObjectContainer* newDOC = makeDisplayObjectContainer(childData);
            newS->addChild(newDOC);
        }
        if(childData["type"] == "Sprite") {
            Sprite* newS2 = makeSprite(childData);
            newS->addChild(newS2);
        }
        if(childData["type"] == "AnimatedSprite") {
            AnimatedSprite* newAS = makeAnimatedSprite(childData);
            newS->addChild(newAS);
        }
    }
    return newS;
}

AnimatedSprite* Scene::makeAnimatedSprite(json data) {
    AnimatedSprite* newAS = new AnimatedSprite(data["id"]);
    newAS->visible = data["visible"];
    newAS->position.x = data["position.x"];
    newAS->position.y = data["position.y"];
    newAS->width = data["width"];
    newAS->height = data["height"];
    newAS->pivot.x = data["pivot.x"];
    newAS->pivot.y = data["pivot.y"];
    newAS->scaleX = data["scaleX"];
    newAS->scaleY = data["scaleY"];
    newAS->rotation = data["rotation"];
    newAS->alpha = data["alpha"];
    newAS->facingRight = data["facingRight"];
    
    string anim = data["animations"]["0"]["name"];
    // Animations
    for(auto& [key, value] : data["animations"].items()) {
        newAS->addAnimation(value["filepath"], value["name"], value["frames"], value["rate"], value["loop"]);
    }
    newAS->play(anim);
 
    // Children
    for(auto& [key, value] : data["children"].items()) {
        json childData = value;
        if(childData["type"] == "DisplayObject") {
            DisplayObject* newDO = makeDisplayObject(childData);
            newAS->addChild(newDO);
        }
        if(childData["type"] == "DisplayObjectContainer") {
            DisplayObjectContainer* newDOC = makeDisplayObjectContainer(childData);
            newAS->addChild(newDOC);
        }
        if(childData["type"] == "Sprite") {
            Sprite* newS = makeSprite(childData);
            newAS->addChild(newS);
        }
        if(childData["type"] == "AnimatedSprite") {
            AnimatedSprite* newAS2 = makeAnimatedSprite(childData);
            newAS->addChild(newAS2);
        }
    }
    return newAS;
}

void Scene::update(set<SDL_Scancode> pressedKeys) {
    DisplayObjectContainer::update(pressedKeys);
}

void Scene::draw(AffineTransform &at) {
    DisplayObjectContainer::draw(at);
}

