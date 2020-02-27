#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <experimental/filesystem>
#include "Sprite.h"
#include "Scene.h"
#include "DevTool.h"

using namespace std;
namespace fs = std::experimental::filesystem;

DevTool::DevTool() : Game(800, 700) {
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
    // sceneWindow = thisScene;
}

void DevTool::save(string filepath)
{
    return;
}

void DevTool::update(set<SDL_Scancode> pressedKeys){
    SDL_Event mouseEvent;
    SDL_PollEvent(&event);
    switch (event.type)
    {
        case SDL_MOUSEBUTTONDOWN:
            
        case SDL_MOUSEBUTTONUP:
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
	Game::draw(at);
}

