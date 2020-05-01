#include "Scene.h"
#include "Game.h"
#include "MyGame.h"
#include "SelectionMenu.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Player.h"
#include "Enemy.h"

Scene::Scene() : DisplayObjectContainer() {
    this->type = "Scene";
}
Scene::~Scene() {
}
//
//Tmx tutorial: https://codeofconnor.com/2017/08/18/how-to-load-and-render-tiled-maps-in-your-sdl2-game/
void Scene::loadTileMap(string tilePath) { //working on parsing in tmx room files 
    json j; 
    ifstream ifs(tilePath);
    ifs >> j;
    //Level Info
    int rows, cols, tile_width, tile_height; 
    sceneNum = j["room"];
    //save coord of entrance/exits of Level 
    for (auto& pt : j["transitionPts"]) {
        SDL_Point temp = {pt["x"], pt["y"]};
        transitionPts.insert(std::pair<string, SDL_Point>(pt["name"], temp));
    }
    //where the char should spawn 
    for (auto& pt : j["charStart"]) {
        SDL_Point temp = {pt["x"], pt["y"]};
        charStart.insert(std::pair<int, SDL_Point>(pt["name"], temp));
    }
    for (auto& pt : j["charEnd"]) {
        SDL_Point temp = {pt["x"], pt["y"]};
        charEnd.insert(std::pair<int, SDL_Point>(pt["name"], temp));
    }
    //level boundaries 
    top = j["top"];
    bottom = j["bottom"];
    right = j["right"];
    left = j["left"];
    rows = j["height"];
    cols = j["width"];
    tile_width = j["tilewidth"];
    tile_height = j["tileheight"];
    //make a new Layer 
    Layer* newLayer = new Layer();
    newLayer->id = "Layer 1";
    newLayer->scrollSpeed = 1;
    this->addChild(newLayer);
    //Loop through tilesets 
    for (auto& tset : j["tilesets"]) {
        //load and save textures for easy access later 
        string path = tset["path"];
        SDL_Surface* image = IMG_Load(path.c_str());
	    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, image);
        this->tilesets.insert(std::pair<int, SDL_Texture*>(tset["firstgid"], texture));
    }
    // cout << "first gid of tset " << tilesets[1] << endl;
    for (auto& layer : j["layers"]) {
        if (layer["type"] != "tilelayer") { //rendering only tile layers
            continue;
        }
        // cout << "after checking layer type" << endl;
         for (int y = 0; y < rows; ++y) {
            for (int x = 0; x < cols; ++x) {
                // cout << "inside nested loop" << endl;
                int tile_index = x + (y * cols);
                int cur_gid = layer["data"][tile_index];
                // cout << "cur_gid " << cur_gid << endl;
                if (cur_gid == 0) {
                    continue;
                }
                int tset_gid = -1; //to check for tile sets
                for (auto ts = this->tilesets.rbegin(); ts != this->tilesets.rend(); ts++) {
                    if (ts->first <= cur_gid) {
                        tset_gid = ts->first;
                        break;
                    }
                }
                if (tset_gid == -1) { //not in the tile set, then skip
                    continue;
                }
                //normalizing the GID
                cur_gid -= tset_gid;
                int ts_width = 0;
                int ts_height = 0;
                // cout << "tset_gid " << this->tilesets[233] << endl;
                SDL_QueryTexture(this->tilesets[tset_gid],
                    NULL, NULL, &ts_width, &ts_height);
                //calculate area to draw on
                double region_x = (cur_gid % (ts_width / tile_width)) * tile_width;
                // cout << "after region x" << endl;
                double region_y = (cur_gid / (ts_width / tile_height)) * tile_height;
                // cout << "after region y" << endl;
                //calculate world position of tile
                int x_pos = x * tile_width;
                int y_pos = y * tile_height;
                //if part of the tiled platform, render a specific region instead of whole thing
                //will remove later if not rendering objects other than the tiled platform
                if (1 <= cur_gid && cur_gid <= 232) {
                    DisplayObject* temp = new DisplayObject();
                    temp->setTexture(tilesets[tset_gid]);
                    temp->position.x = x_pos; 
                    temp->position.y = y_pos; 
                    temp->width = tile_width; 
                    temp->height = tile_height; 
                    temp->visible = true;
                    temp->scaleX = 1;
                    temp->scaleY = 1;
                    temp->alpha = 255;
                    temp->facingRight = true;
                    if (cur_gid == 159 || cur_gid == 158 || cur_gid < 130) {
                        // cout << "cur_gid " << cur_gid << endl;
                        temp->gameType = "grass";
                    }
                    else {
                        temp->gameType = "platform";
                    }
                    temp->srcrect.x = region_x; 
                    temp->srcrect.y = region_y; 
                    temp->srcrect.w = tile_width; 
                    temp->srcrect.h = tile_height;  
                    temp->tile = true;
                    newLayer->addChild(temp);
                }
            }
         }
    }
}
DisplayObject* Scene::getObject(){
    return this->curObj;
}
DisplayObject* Scene::getEnemy(){
    return this->curEnemy;
}
Enemy* Scene::getRealEnemy(){
    return this->enemy;
}
void Scene::setEnemy(DisplayObject* enemy){
    this->curEnemy = enemy;
}
void Scene::setRealEnemy(Enemy* enemy){
    this->enemy = enemy;
}
AnimatedSprite* Scene::getCharacter(){
    return this->character;
}
Player* Scene::getPlayer(){
    return this->player;
}
void Scene::setPlayer(Player* chara) {
    this->player = chara;
}
int Scene::getSceneNum(){
    return this->sceneNum;
}


// void Scene::loadEnviron(string filepath) {
//     json j;
//     ifstream ifs(filepath);
//     ifs >> j;
//     for (auto& i : j[""])
// }
void Scene::loadScene(string sceneFilePath) {
    json j;
    ifstream ifs(sceneFilePath);
    ifs >> j;

    // this->id = j["id"]["name"];
    
    int i = 0;
    for(auto& [key, value] : j.items()) {
        json data = value;
        // cout << "hi" << endl;
        // cout << data["type"] << endl;
         //quick fix: find j["character"], set it to root & call in myGame
        if(data["type"] == "DisplayObject") {
            DisplayObject* newDC = makeDisplayObject(data);
            this->addChild(newDC);
        }
        if(data["type"] == "DisplayObjectContainer") {
            DisplayObjectContainer* newDOC = makeDisplayObjectContainer(data);
            this->addChild(newDOC);
           
        }
        if(data["type"] == "Sprite") {
            Sprite* newS = makeSprite(data);
            this->addChild(newS);
        }
        if(data["type"] == "Layer") {
            Layer* newLayer = makeLayer(data);
            this->addChild(newLayer);
        }
        //just distinguish root from rest of animated sprites 
        if(data["type"] == "AnimatedSprite") {
            AnimatedSprite* newAS = makeAnimatedSprite(data); 
            this->addChild(newAS);
        }
        if(data["type"] == "Enemy") {
            Sprite* newS = makeEnemy(data);
            this->addChild(newS);
        }
    }
    ifs.close();
}

json Scene::toJson() {
    json j;

    for(auto* entity : this->children) {
        json temp = parse(entity);
        j.push_back(json::object_t::value_type(entity->id, temp));
    }


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

    // Animations
    if(obj->type == "AnimatedSprite") {
        json anim;
        AnimatedSprite* tempSpr = dynamic_cast<AnimatedSprite*>(obj);
        for(int i = 0; i < tempSpr->animationNames.size(); i++) {
            json tempJson;
            Animation* tempAni = tempSpr->getAnimation(tempSpr->animationNames[i]);
            
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
        DisplayObjectContainer* doc = dynamic_cast<DisplayObjectContainer*>(obj);
        for(auto* child : doc->children) {
            json temp = parse(child);
            childs += json::object_t::value_type(temp["id"], temp);
        }
        j += json::object_t::value_type("children", childs);
    }

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
    newDO->gameType = data["gameType"];
    
    return newDO;
}

DisplayObjectContainer* Scene::makeDisplayObjectContainer(json data) {
    DisplayObjectContainer* newDOC = new DisplayObjectContainer();
    newDOC->id = data["id"];
    newDOC->visible = data["visible"];
    newDOC->position.x = data["position.x"];
    newDOC->position.y = data["position.y"];
    // cout << data["id"] << endl;
    newDOC->gameType = data["gameType"];
    newDOC->width = data["width"];
    newDOC->height = data["height"];
    newDOC->pivot.x = data["pivot.x"];
    newDOC->pivot.y = data["pivot.y"];
    newDOC->scaleX = data["scaleX"];
    newDOC->scaleY = data["scaleY"];
    newDOC->rotation = data["rotation"];
    newDOC->alpha = data["alpha"];
    newDOC->facingRight = data["facingRight"];
    newDOC->gameType = data["gameType"];
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

Layer* Scene::makeLayer(json data) {
    Layer* newLayer = new Layer();
    newLayer->id = data["id"];
    newLayer->scrollSpeed = data["scroll"];
    if(data["filepath"] != "") {
        newLayer->imgPath = data["filepath"];
        newLayer->loadTexture(data["filepath"]);
    }

    // Children
    for(auto& [key, value] : data["children"].items()) {
        json childData = value;
        if(childData["type"] == "DisplayObject") {
            DisplayObject* newDO = makeDisplayObject(childData);
            newLayer->addChild(newDO);
            if (childData["gameType"] == "enemy") {
                enemies.push_back(make_pair(childData["id"], newDO));
            }
            else if (childData["gameType"] == "platform") {
                objects.push_back(make_pair(childData["id"], newDO));
            }
        }
        if(childData["type"] == "DisplayObjectContainer") {
            DisplayObjectContainer* newDOC = makeDisplayObjectContainer(childData);
            newLayer->addChild(newDOC);
            //  if (childData["id"] == "enemy") {
            //     enemies.push_back(newDOC);
            // }
        }
        if(childData["type"] == "Sprite") {
            Sprite* newS = makeSprite(childData);
            newLayer->addChild(newS);
        }
        if(childData["type"] == "AnimatedSprite") {
            AnimatedSprite* newAS = makeAnimatedSprite(childData); //possibly use root var
            newLayer->addChild(newAS);
            this->character = newAS;
        }
        if(childData["type"] == "Player") {
            Player* newP = makePlayer(childData); //possibly use root var
            newLayer->addChild(newP);
            this->player = newP; 
        }
         if(childData["type"] == "Enemy") {
            Enemy* newP = makeEnemy(childData); //possibly use root var
            newLayer->addChild(newP);
            this->enemy = newP; 
        }
    }
    // cout << "children of newLayer " << newLayer->children.size() << endl;
    return newLayer;
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
    //make from spritesheet 
    //AnimatedSprite* newAS = new AnimatedSprite(data["id"], data["filepath"], data["xmlpath"]);
    AnimatedSprite* newAS;
    Player* newplayer;
    if (data["useSpriteSheet"]) {
         newAS = new Player(data["id"], true);
    }
    else {
        newAS = new AnimatedSprite(data["id"]);
        for(auto& [key, value] : data["animations"].items()) {
            newAS->addAnimation(value["filepath"], value["name"], value["frames"], value["rate"], value["loop"]);
        }
    }

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
    newAS->srcrect.x = 0;
    newAS->srcrect.y = 0;
    newAS->gameType = data["gameType"];


    string anim = data["animations"]["0"]["name"];
    // Animations
    // cout << "Anim name " << anim << endl;
    newAS->play(anim);
    //newplayer->play(anim);
 
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
Player* Scene::makePlayer(json data){
    Player* newplayer;
    newplayer = new Player(data["id"], true);
    // newplayer->addSSAnimation(data["animations"]["0"]["filepath"], 
    //     data["animations"]["0"]["xmlpath"]);
    
    // AnimatedSprite* newAS = new AnimatedSprite(data["id"]);
   // newplayer = newAS;
    // (newplayer->id != "null"){
    newplayer->visible = data["visible"];
    newplayer->position.x = data["position.x"];
    newplayer->position.y = data["position.y"];
    newplayer->width = data["width"];
    newplayer->height = data["height"];
    newplayer->pivot.x = data["pivot.x"];
    newplayer->pivot.y = data["pivot.y"];
    newplayer->scaleX = data["scaleX"];
    newplayer->scaleY = data["scaleY"];
    newplayer->rotation = data["rotation"];
    newplayer->alpha = data["alpha"];
    newplayer->facingRight = data["facingRight"];
    
    newplayer->gameType = data["gameType"];


    string anim = data["animations"]["0"]["name"];
    // Animations
    newplayer->play(anim);
 
    // Children
    for(auto& [key, value] : data["children"].items()) {
        json childData = value;
        if(childData["type"] == "DisplayObject") {
            DisplayObject* newDO = makeDisplayObject(childData);
            newplayer->addChild(newDO);
        }
        if(childData["type"] == "DisplayObjectContainer") {
            DisplayObjectContainer* newDOC = makeDisplayObjectContainer(childData);
            newplayer->addChild(newDOC);
        }
        if(childData["type"] == "Sprite") {
            Sprite* newS = makeSprite(childData);
            newplayer->addChild(newS);
        }
        if(childData["type"] == "AnimatedSprite") {
            AnimatedSprite* newAS2 = makeAnimatedSprite(childData);
            newplayer->addChild(newAS2);
        }
    }
    return newplayer;

}
Enemy* Scene::makeEnemy(json data) {
    Enemy* newS = new Enemy(data["id"], data["filepath"]);
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
void Scene::update(set<SDL_Scancode> pressedKeys, set<SDL_GameControllerButton> pressedButtons, set<pair<SDL_GameControllerAxis, float>> movedAxis) {
    if (this->sceneNum == 7 && 
       ( this->player->position.y > this->transitionPts["from5Greater"].y && 
        (this->player->position.x > this->transitionPts["from5Greater"].x && this->player->position.x < this->transitionPts["from5Less"].x)))
    {
        //call change scene event
        MyGame::eDispatcher->dispatchEvent(new Event(CHANGE, MyGame::eDispatcher, this->player,
            "./resources/scenes/area1files/Area1Room5.json"));
    }
    //if the scene isn't a battle and the character collided with an enemy 
    if (!isBattle && this->player->inBattle && this->player->enemy != NULL) {
        cout << "in battle!" << endl;
        this->curEnemy = this->player->enemy;
        MyGame::eDispatcher->dispatchEvent(new Event(FIGHT, MyGame::eDispatcher, this->player, this->curEnemy));
        isBattle = true;
        this->player->enemy = NULL;
        this->player->inBattle = false;
    }
    if (this->sceneNum == 5 && 
       ( this->player->position.y > this->transitionPts["to7Greater"].y && this->player->position.y < this->transitionPts["to7Less"].y)
        && (this->player->position.x > this->transitionPts["to7Greater"].x && this->player->position.x < this->transitionPts["to7Less"].x))
    {
        //call change scene event
        MyGame::eDispatcher->dispatchEvent(new Event(CHANGE, MyGame::eDispatcher, this->player,
            "./resources/scenes/area1files/Area1Room7.json"));
    }
    //revert from battle to previous scene 
    //if (isBattle && keyboard press or something to get out?)
    DisplayObjectContainer::update(pressedKeys, pressedButtons, movedAxis);
}

void Scene::draw(AffineTransform &at) {
    DisplayObjectContainer::draw(at);
}

