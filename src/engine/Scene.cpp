#include "Scene.h"
#include <iostream>
#include <fstream>
#include <string>
#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>

Scene::Scene() : DisplayObjectContainer() {
    this->type = "Scene";
}
//Tmx tutorial: https://codeofconnor.com/2017/08/18/how-to-load-and-render-tiled-maps-in-your-sdl2-game/
void Scene::loadTileMap(string tilePath, bool isNextMap) { //working on parsing in tmx room files 
    tmx::Map map;
    map.load(tilePath);
    auto map_dim = map.getTileCount();
    int rows, cols, tile_width, tile_height;

    //get dimensions of tile map
    rows = map_dim.y;
    cols = map_dim.x;
    //create new Layer 
    Layer* newLayer = new Layer();
    newLayer->id = "Layer 1";
    newLayer->scrollSpeed = 1;
    this->addChild(newLayer);
   
    //get Tile size, width, height of map
    auto tilesize = map.getTileSize();
    tile_width = tilesize.x;
    tile_height = tilesize.y;
    
    auto& map_tilesets = map.getTilesets();
    SDL_Point sdl_ts;
    for (auto& tset : map_tilesets) {
        //save the SDL_textures somewhere
        DisplayObject* temp = new DisplayObject("", tset.getImagePath()); 
        auto tex = temp->curTexture;
        this->tilesets.insert(std::pair<int, SDL_Texture*>(tset.getFirstGID(), tex));
        this->tileDO.insert(std::pair<int, DisplayObject*>(tset.getFirstGID(), temp));
    }
    
    //main loop
    auto& map_layers = map.getLayers(); 
    for (auto& layer : map_layers) {
        if (layer->getType() != tmx::Layer::Type::Tile) { //rendering only tile layers
            continue;
        }
        //get tile layers 
        auto* tile_layer = dynamic_cast<const tmx::TileLayer*>(layer.get()); 
        // Grab all of this layer's tiles.
        auto& layer_tiles = tile_layer->getTiles();
        //Loop through all tiles
        for (auto y = 0; y < rows; ++y) {
            for (auto x = 0; x < cols; ++x) {
                auto tile_index = x + (y * cols);
                //loop through each tile and save information
                auto cur_gid = layer_tiles[tile_index].ID;
                // If the GID is 0, skip
                if (cur_gid == 0) {
                    continue;
                }
                //check if the tile is in the tileset by comparing GID 
                //if first tileset's GID <= GID of tileset, then save tile GID 
                auto tset_gid = -1; //to check for tile sets
                // cout << "Size of tilesets " << tilesets.size() << endl;
                //for( auto it = x.begin(); it != x.end(); i++)
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
                // cout << "tset_gid " << tset_gid << endl;
                auto ts_width = 0;
                auto ts_height = 0;
                SDL_QueryTexture(this->tilesets[tset_gid],
                    NULL, NULL, &ts_width, &ts_height);
                
                //calculate area to draw on
                auto region_x = (cur_gid % (ts_width / tile_width)) * tile_width;
                auto region_y = (cur_gid / (ts_width / tile_height)) * tile_height;
                //calculate world position of tile
                auto x_pos = x * tile_width;
                auto y_pos = y * tile_height;
                //save tile info in the vector 
                //x_pos, y_pos, tile_width=w, tile_height=h
                //include region_x and y?? like the origin I guess..
                DisplayObject* temp = new DisplayObject("", this->tileDO[tset_gid]->imgPath);
                // cout << tilesets[tset_gid] << endl;
                temp->position.x = x_pos; 
                temp->position.y = y_pos; 
                temp->width = tile_width; 
                temp->height = tile_height; 
                if (1 <= cur_gid && cur_gid <= 232) {
                    temp->srcrect.x = region_x; 
                    temp->srcrect.y = region_y; 
                    temp->srcrect.w = tile_width; 
                    temp->srcrect.h = tile_height;  
                }
                else {
                    temp->srcrect.x = 0; 
                    temp->srcrect.y = 0; 
                }
                temp->visible = true;
                temp->scaleX = 1;
                temp->scaleY = 1;
                temp->alpha = 255;
                temp->facingRight = true;
                newLayer->addChild(temp);
                // cout << "loading" << endl;
                //for the number of tilesets, if part of this tileset i
                    //DisplayObject temp = new DisplayObject("",tileset[i].imgpath)
                    //temp->position.x = x_pos...etc.
            }
        }
    }
     //to initialize character or not
    if (!isNextMap) {
        json j;
        ifstream ifs("./resources/scenes/char.json");
        ifs >> j;
        AnimatedSprite* newAS = makeAnimatedSprite(j["character"]); 
        newLayer->addChild(newAS);
        this->character = newAS;
    }
}
DisplayObject* Scene::getObject(int index){
    return this->objects[index];
}
AnimatedSprite* Scene::getCharacter(){
    return this->character;
}
void Scene::loadScene(string sceneFilePath) {
    json j;
    ifstream ifs(sceneFilePath);
    ifs >> j;
    // int i = 0;
    for(auto& [key, value] : j.items()) {
        json data = value;
         //quick fix: find j["character"], set it to root & call in myGame
        if(data["type"] == "DisplayObject") {
            DisplayObjectContainer* newDOC = makeDisplayObjectContainer(data);
            this->addChild(newDOC);
        }
        if(data["type"] == "Sprite") {
            Sprite* newS = makeSprite(data);
            this->addChild(newS);
        }
        if(data["type"] == "Layer") { // This is probably not needed?
            Layer* newLayer = makeLayer(data);
            this->addChild(newLayer);
        }
        //just distinguish root from rest of animated sprites 
        if(data["type"] == "AnimatedSprite") {
            AnimatedSprite* newAS = makeAnimatedSprite(data); 
            this->addChild(newAS);
        }
    }
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
            if (childData["id"] == "coin" || childData["id"] == "questComplete") {
                this->objects.push_back(newDO);
            }
        }
        if(childData["type"] == "DisplayObjectContainer") {
            DisplayObjectContainer* newDOC = makeDisplayObjectContainer(childData);
            newLayer->addChild(newDOC);
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
    }
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
    newAS->srcrect.x = 0;
    newAS->srcrect.y = 0;
    
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

