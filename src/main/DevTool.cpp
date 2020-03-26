#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <experimental/filesystem>
#include "Sprite.h"
#include "Scene.h"
#include "DevTool.h"

const int WINDOW_X = 800;
const int WINDOW_Y = 700;
// const int TILE_SIZE = 40;
#define TILE_SIZE SPRITESIZE

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

    cam = new Camera();
    cam->addChild(currentScene);
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
            tileMenu->addChild(new DisplayObjectContainer(path, path));
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

void DevTool::start(){

	int ms_per_frame = (1.0/(double)this->frames_per_sec)*1000;
	std::clock_t start = std::clock();

	bool quit = false;
	SDL_Event event;

	while(!quit){
        // cout << "next loop" << endl;
		std::clock_t end = std::clock();
		double duration = (( end - start ) / (double) CLOCKS_PER_SEC)*1000;
		if(duration > ms_per_frame){
			start = end;
            // cout << "before update" << endl;
			this->update(pressedKeys);
			AffineTransform at;
            // cout << "before draw" << endl;
			this->draw(at);
		}
        cout << "poll events" << endl;
		SDL_PollEvent(&event);
		switch (event.type)
		{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				pressedKeys.insert(event.key.keysym.scancode);
				break;
			case SDL_KEYUP:
				pressedKeys.erase(event.key.keysym.scancode);
				break;
            // case SDL_FINGERDOWN:
            //     cout << "finger event" << endl;
            //     if (initMouseLoc.x == -1 && initMouseLoc.y == -1)
            //     {
            //         initMouseLoc = {(int)mouseEvent.tfinger.x, (int)mouseEvent.tfinger.y};
            //         if (initMouseLoc.y >= this->windowHeight - SPRITESIZE)
            //         {
            //             cout << "selecting from tile menu" << endl;
            //             int ind = (int)((initMouseLoc.x - tileMenu->position.x)/SPRITESIZE);
            //             if (ind < tileMenu->children.size())
            //             {
            //                 selected = tileMenu->children[ind];
            //             }
            //             DisplayObject *temp = new DisplayObject("selected", 200, 0, 0);
            //             temp->alpha = 70;
            //             ((DisplayObjectContainer *)selected)->addChild(temp);
            //         }
            //     }
            //     break;
            case SDL_MOUSEBUTTONDOWN:
                cout << initMouseLoc.x << endl;
                cout << "mousedown event" << endl;
                if (initMouseLoc.x == -1 && initMouseLoc.y == -1)
                {
                    cout << "first click" << endl;
                    initMouseLoc = {event.button.x, event.button.y};
                    cout << "mouse loc: " << initMouseLoc.x << "' " << initMouseLoc.y << endl;
                    if (selected)
                    {
                        cout << "resetting selection" << endl;
                        selected->removeImmediateChild("selected");
                        selected = NULL;
                    }
                    if (initMouseLoc.y >= this->windowHeight - SPRITESIZE)
                    {
                        cout << "selecting from tile menu" << endl;
                        int ind = (int)((initMouseLoc.x - tileMenu->position.x)/SPRITESIZE);
                        if (ind < tileMenu->children.size())
                        {
                            cout << "found selection: " << ind << endl;
                            selected = (DisplayObjectContainer *)tileMenu->children[ind];
                        }
                        cout << "finished selection" << endl;
                        DisplayObject *temp = new DisplayObject("selected", 200, 0, 0);
                        temp->alpha = 70;
                        cout << "plz work" << endl;
                        selected->addChild(temp);
                        cout << " made selection box" << endl;
                    }
                    else
                    {  
                        cout << "in scene window" << endl;
                        selected = NULL;
                        cout << "not here" << endl;
                    }
                }
                else
                {
                    if (selected)
                    {
                        selected->position.x += event.button.x - initMouseLoc.x;
                        selected->position.y += event.button.y - initMouseLoc.y;
                        initMouseLoc = {event.button.x, event.button.y};
                    }
                    cout << "changing position to: " << event.button.x << ", " << event.button.y << endl;
                }
                cout << "broke out of switch" << endl;
                break;
            // case SDL_MOUSEMOTION:
            //     if (selected && initMouseLoc.x != -1 && initMouseLoc.y != -1)
            //     {
            //         selected->position.x += event.motion.x - initMouseLoc.x;
            //         selected->position.y += event.motion.y - initMouseLoc.y;
            //         initMouseLoc = {event.motion.x, event.motion.y};
            //         cout << "changing position to: " << event.motion.x << ", " << event.motion.y << endl;
            //     }
            case SDL_MOUSEBUTTONUP:
                cout << "mouse up" << endl;
                if (selected && initMouseLoc.x != -1 && initMouseLoc.y != -1)
                {
                    selected->position.x += event.button.x - initMouseLoc.x;
                    selected->position.y += event.button.y - initMouseLoc.y;

                    // Snap to tile
                    int posX, posY;
                    posX = selected->position.x;
                    posY = selected->position.y;
                    selected->position.x = posX - (posX % TILE_SIZE);
                    selected->position.y = posY - (posY % TILE_SIZE);
                    // initMouseLoc = {event.button.x, event.button.y};
                    cout << "changing position to: " << event.button.x << ", " << event.button.y << endl;
                }
                initMouseLoc = {-1, -1};
                break;
		}
	
	}
}


void DevTool::update(set<SDL_Scancode> pressedKeys){

    // Read keyboard inputs

    for (SDL_Scancode keys: pressedKeys) {
        switch(keys) {
            case SDL_SCANCODE_Q:
                tileMenu->position.x -= 5;
                break;
            case SDL_SCANCODE_W:
                tileMenu->position.x += 5;
                break;
            case SDL_SCANCODE_UP:
                cam->position.y += 5;
                break;
            case SDL_SCANCODE_DOWN:
                cam->position.y -= 5;
                break;
            case SDL_SCANCODE_LEFT:
                cam->position.x += 5;
                break;
            case SDL_SCANCODE_RIGHT:
                cam->position.x -= 5;
                break;
            case SDL_SCANCODE_S:
                {
                    cout << "Please enter the relative filepath to where you want to save the JSON:\n";
                    string savepath;
                    cin >> savepath;
                    save(savepath);
                    break; 
                }
            case SDL_SCANCODE_L:
                {
                    cout << "Please enter the relative filepath to the JSON file you want to import:\n";
                    string loadpath;
                    cin >> loadpath;
                    load(loadpath);
                    break; 
                }
        }
    }
    // if(pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end() && change) {
    //     instance->removeImmediateChild(currentScene);
    //     currentScene = scene2;
    //     instance->addChild(currentScene);
    //     change = !change;
    // }
	Game::update(pressedKeys);
}

void DevTool::draw(AffineTransform &at){ //have to remove selection box before saving then add it back in after
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
