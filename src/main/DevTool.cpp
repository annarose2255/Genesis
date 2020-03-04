#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <experimental/filesystem>
#include "Sprite.h"
#include "Scene.h"
#include "DevTool.h"

const int WINDOW_X = 800;
const int WINDOW_Y = 700;
const int TILE_SIZE = 40;

using namespace std;
namespace fs = std::experimental::filesystem;

DevTool::DevTool() : Game(WINDOW_X, WINDOW_Y) {
    if (SDL_Init(SDL_INIT_EVENTS) != 0){
        cout << "Unable to initialize Events" << endl;
    }
	instance = this;
    tileMenu = new DisplayObjectContainer();
    sceneWindow = new DisplayObjectContainer();
    tileMenu->position={0, instance->windowHeight - SPRITESIZE};
	instance->addChild(tileMenu);
    instance->addChild(sceneWindow);
    cout << "initted" << endl;
    IterateDirectory("resources");
}

void DevTool::IterateDirectory(string filepath)
{
    for(auto& p: fs::directory_iterator(filepath))
    {
        // cout << p.path() << endl;
        fs::file_status s = p.status();
        string path = p.path();
        if (fs::is_regular_file(s))
        {
            size_t fileTypeInd = path.find_last_of('.');
            // cout << path.substr(fileTypeInd) << endl;
            if (path.substr(fileTypeInd + 1).compare("png") != 0)
            {
                continue;
            }
            tileMenu->addChild(new DisplayObject(path, path));
            tileMenu->children.back()->position = {(int)(tileMenu->children.size()-1)*SPRITESIZE};
        }
        else if (fs::is_directory(s))
        {
            IterateDirectory(p.path());
        }
    }
}

DevTool::~DevTool(){
    delete tileMenu;
    delete sceneWindow;
    
}

void DevTool::load(string filepath)
{
    Scene *thisScene = new Scene();
    thisScene->loadScene(filepath);
    sceneWindow->addChild(thisScene);
    currentScene = thisScene;
    // sceneWindow = thisScene;
}

void DevTool::save(string filepath)
{
    ofstream saveFile;
    saveFile.open(filepath);
    
    json saveData = currentScene->toJson();
    string data = saveData.dump(4);
    
    saveFile << data;
    saveFile.close();
}

void DevTool::update(set<SDL_Scancode> pressedKeys){
    // cout << SDL_PollEvent(&mouseEvent) << endl;
    while(SDL_PollEvent(&mouseEvent))
    {
        cout << mouseEvent.type << ",  " << SDL_FINGERDOWN << ", " << SDL_MOUSEBUTTONDOWN << endl;
        switch (mouseEvent.type)
        {
            case SDL_FINGERDOWN:
                cout << "mousedown event" << endl;
                if (initMouseLoc.x == -1 && initMouseLoc.y == -1)
                {
                    initMouseLoc = {(int)mouseEvent.tfinger.x, (int)mouseEvent.tfinger.y};
                    if (initMouseLoc.y >= this->windowHeight - SPRITESIZE)
                    {
                        cout << "selecting from tile menu" << endl;
                        int ind = (int)((initMouseLoc.x - tileMenu->position.x)/SPRITESIZE);
                        if (ind < tileMenu->children.size())
                        {
                            selected = tileMenu->children[ind];
                        }
                        DisplayObject *temp = new DisplayObject("selected", 200, 0, 0);
                        temp->alpha = 70;
                        ((DisplayObjectContainer *)selected)->addChild(temp);
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                cout << "mousedown event" << endl;
                if (initMouseLoc.x == -1 && initMouseLoc.y == -1)
                {
                    initMouseLoc = {mouseEvent.button.x, mouseEvent.button.y};
                    if (initMouseLoc.y >= this->windowHeight - SPRITESIZE)
                    {
                        cout << "selecting from tile menu" << endl;
                        int ind = (int)((initMouseLoc.x - tileMenu->position.x)/SPRITESIZE);
                        if (ind < tileMenu->children.size())
                        {
                            selected = tileMenu->children[ind];
                        }
                        DisplayObject *temp = new DisplayObject("selected", 200, 0, 0);
                        temp->alpha = 70;
                        ((DisplayObjectContainer *)selected)->addChild(temp);
                    }
                }
                break;
            case SDL_MOUSEBUTTONUP:
                break;
        }
    }

    if (pressedKeys.find(SDL_SCANCODE_Q) != pressedKeys.end())
    {
        tileMenu->position.x -= 5;
    }
    if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end())
    {
        tileMenu->position.x += 5;
    }
    if (pressedKeys.find(SDL_SCANCODE_S) != pressedKeys.end())
    {
        cout << "Please enter the relative filepath to where you want to save the JSON:\n";
        string filepath;
        cin >> filepath;
        save(filepath);
    }
    if (pressedKeys.find(SDL_SCANCODE_L) != pressedKeys.end())
    {
        cout << "Please enter the relative filepath to the JSON file you want to import:\n";
        string filepath;
        cin >> filepath;
        load(filepath);
    }
    // if(pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end() && change) {
    //     instance->removeImmediateChild(currentScene);
    //     currentScene = scene2;
    //     instance->addChild(currentScene);
    //     change = !change;
    // }
	Game::update(pressedKeys);
}

void DevTool::draw(AffineTransform &at){
	// Game::draw(at);
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
    SDL_RenderClear(Game::renderer);
    DevTool::drawGrid();
	DisplayObjectContainer::draw(at);
	SDL_RenderPresent(Game::renderer);
}

void DevTool::drawGrid(){
    SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    for (int i = 0; i < WINDOW_Y / TILE_SIZE; i++){
        SDL_RenderDrawLine(Game::renderer, 0, i * TILE_SIZE, WINDOW_X, i * TILE_SIZE);
    }
    for (int i = 0; i < WINDOW_X / TILE_SIZE; i++){
        SDL_RenderDrawLine(Game::renderer, i * TILE_SIZE, 0, i * TILE_SIZE, WINDOW_Y);
    }
}
