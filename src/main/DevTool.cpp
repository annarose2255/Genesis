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

    // Initialize what we will see
    tileMenu = new DisplayObjectContainer();
    cout << "tileMenu camPerspective: " << tileMenu->camPerspective << endl;
    sceneWindow = new Scene();
    currentScene = new Scene();
    tileMenu->position={0, instance->windowHeight - SPRITESIZE};

    sceneWindow->addChild(currentScene);

	instance->addChild(tileMenu); 
    Game::camera->addChild(sceneWindow);
    instance->addChild(Game::camera);

// 	instance->addChild(tileMenu);
//     instance->addChild(sceneWindow);
//     tileMenu -> camPerspective = false;
//     sceneWindow -> camPerspective = false;
// >>>>>>> Engine
    cout << "initted" << endl;
    IterateDirectory("resources");

}

/*
 * Iterates through every directory in search of .png files
 * Adds those images to the tile menu as a DOC
*/
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
            cout << path << endl;
            path = "./" + path;
            tileMenu->addChild(new DisplayObjectContainer(path, path));
            tileMenu->children.back()->position = {(int)(tileMenu->children.size()-1)*SPRITESIZE};
            cout << tileMenu->children.back()->position.x << " " << tileMenu->children.back()->position.y << endl;
        }
        else if (fs::is_directory(s))
        {
            IterateDirectory(p.path());
        }
    }
    cout << tileMenu->children.back()->position.x << " " << tileMenu->children.back()->position.y << endl;
    cout << Game::camera->position.x << " " << Game::camera->position.y << endl;
}

DevTool::~DevTool(){
    delete tileMenu;
    delete sceneWindow;
    
}

void DevTool::load(string filepath)
{
    //Scene *thisScene = new Scene();
    // sceneWindow->loadScene(filepath);
    //add in loadTileMap() option
    string tmx_suffix = "tmx";
    if ((0 == filepath.compare(filepath.length() - tmx_suffix.length(), tmx_suffix.length(), tmx_suffix))){
        sceneWindow->loadTileMap(filepath);
    } 
    else {
        sceneWindow->loadScene(filepath);
    }
    // sceneWindow = thisScene;
    // currentScene = thisScene;
    // sceneWindow = thisScene;
}

void DevTool::save(string filepath)
{
    ofstream saveFile;
    saveFile.open(filepath);
    
    // json saveData;
    // saveData = currentScene->toJson();

    string data = sceneWindow->toJson().dump(4);
    saveFile << data;
    saveFile.close();
}

DisplayObjectContainer *DevTool::sceneClick(int x, int y)
{
    cout << "mouse click: " << x << "," << y <<endl;
    return sceneClickHelper(sceneWindow, x, y);
}

bool DevTool::inSquare(DisplayObjectContainer *parent, int x, int y)
{
    return parent->position.x <= x && parent->position.x + SPRITESIZE >= x && parent->position.y <= y && parent->position.y + SPRITESIZE >= y;
}

DisplayObjectContainer *DevTool::sceneClickHelper(DisplayObjectContainer *parent, int x, int y)
{
    cout << "is inside: " << inSquare(parent, x, y) << endl;
    if (inSquare(parent, x, y))
    {
        return parent;
    }
    AffineTransform *gt = new AffineTransform();
    parent->applyTransformations(*gt);
    SDL_Point newPoint = gt->transformPoint(x, y);
    delete gt;
    cout << "transformed point: " << newPoint.x << "," << newPoint.y <<endl;
    DisplayObjectContainer *ret = NULL;
    for (DisplayObject *objChildren : parent->children)
    {
        ret = sceneClickHelper((DisplayObjectContainer *)objChildren, newPoint.x, newPoint.y);
        if (ret)
        {
            cout << "returning" << endl;
            return ret;
        }
    }
    cout << "returning null" << endl;
    return ret;
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
			this->update(pressedKeys, controllerInput);
			AffineTransform at;
            // cout << "before draw" << endl;
			this->draw(at);
		}
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
            case SDL_MOUSEBUTTONDOWN:
                // cout << initMouseLoc.x << endl;
                // cout << "mousedown event" << endl;
                currMouseLoc = {event.button.x, event.button.y};
                if (initMouseLoc.x == -1 && initMouseLoc.y == -1)
                {
                    //cout << "first click" << endl;
                    initMouseLoc = {event.button.x, event.button.y};
                    if (selected)
                    {
                        // cout << "resetting selection" << endl;
                        selected->removeImmediateChild("selected");
                        selected = NULL;
                    }
                    if (initMouseLoc.y >= this->windowHeight - SPRITESIZE)
                    {
                        // cout << "selecting from tile menu" << endl;
                        int ind = (int)((initMouseLoc.x - tileMenu->position.x)/SPRITESIZE);
                        if (ind < tileMenu->children.size())
                        {
                            // cout << "found selection: " << ind << endl;
                            selected = (DisplayObjectContainer *)tileMenu->children[ind];
                        }
                        // cout << "finished selection" << endl;
                        DisplayObjectContainer *temp = new DisplayObjectContainer("selected", 200, 0, 0);
                        temp->alpha = 70;
                        // cout << "plz work" << endl;
                        selected->addChild(temp);
                        // cout << " made selection box" << endl;
                    }
                    else
                    {  
                        // cout << "in scene window" << endl;
                        selected = sceneClick(event.button.x, event.button.y);
                        
                        if (selected)  //clicked on a sprite
                        {
                            DisplayObjectContainer *temp = new DisplayObjectContainer("selected", 200, 0, 0);
                            temp->alpha = 70;
                            selected->addChild(temp);
                        }
                        // cout << "not here" << endl;
                    }
                }
                break;
            case SDL_MOUSEBUTTONUP:
                // cout << "mouse up" << endl;
                currMouseLoc = {event.button.x, event.button.y};
                if (selected && initMouseLoc.x != -1 && initMouseLoc.y != -1)
                {
                    //tile menu
                    if (initMouseLoc.y >= this->windowHeight - SPRITESIZE)
                    {
                        if (event.button.y <(this->windowHeight - SPRITESIZE))
                        {
                            selected->removeImmediateChild("selected");
                            string nameID = selected->id + to_string(num);
                            selected = new DisplayObjectContainer(nameID, selected->imgPath);
                            int loc = (int)((initMouseLoc.x)/SPRITESIZE);
                            selected->position = {loc*SPRITESIZE, this->windowHeight - SPRITESIZE};
                            sceneWindow->addChild(selected);
                            DisplayObjectContainer *temp = new DisplayObjectContainer("selected", 200, 0, 0);
                            temp->alpha = 70;
                            selected->addChild(temp);
                            cout << "creating copy" << endl;
                            num++;
                        }
                    }
                    if (event.button.y <(this->windowHeight - SPRITESIZE))
                    {
                        // selected->position.x += event.button.x - initMouseLoc.x;
                        // selected->position.y += event.button.y - initMouseLoc.y;
                        selected->position.x = event.button.x;
                        selected->position.y = event.button.y;
                        // Snap to tile
                        tileSnap(selected);
                    }
                
                    // initMouseLoc = {event.button.x, event.button.y};
                    // cout << "changing position to: " << event.button.x << ", " << event.button.y << endl;
                }
                initMouseLoc = {-1, -1};
                break;
            case SDL_MOUSEMOTION:
                currMouseLoc = {event.motion.x, event.motion.y};
                // cout << "mouse location: " << currMouseLoc.x << "," << currMouseLoc.y <<endl;
                break;
		}
	
	}
}

void DevTool::tileSnap(DisplayObjectContainer *obj)
{
    int posX, posY;
    posX = obj->position.x;
    posY = obj->position.y;
    obj->position.x = posX - (posX % TILE_SIZE);
    obj->position.y = posY - (posY % TILE_SIZE);
    // if (posX % TILE_SIZE > TILE_SIZE/2)
    // {
    //     obj->position.x += TILE_SIZE;
    // }
    // if (posY % TILE_SIZE > TILE_SIZE/2)
    // {
    //     obj->position.y += TILE_SIZE;
    // }
}

void DevTool::paste()
{
    int x, y;
    x = currMouseLoc.x;
    y = currMouseLoc.y;
    if (copied && ! sceneClick(x, y))
    {
        cout << "pasting" << endl;
        DisplayObjectContainer *temp = new DisplayObjectContainer(copied->id, copied->imgPath);
        sceneWindow->addChild(temp);
        cout << "mouse location: " << currMouseLoc.x << "," << currMouseLoc.y <<endl;
        temp->position = {x, y};
        tileSnap(temp);
    }
}
void DevTool::update(set<SDL_Scancode> pressedKeys,  ControllerInput controllerInput){

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
                Game::camera->position.y += 5;
                break;
            case SDL_SCANCODE_DOWN:
                Game::camera->position.y -= 5;
                break;
            case SDL_SCANCODE_LEFT:
                Game::camera->position.x += 5;
                break;
            case SDL_SCANCODE_RIGHT:
                Game::camera->position.x -= 5;
            case SDL_SCANCODE_C:
                if (selected)
                {
                    copied = selected;
                }
                break;
            case SDL_SCANCODE_V:
                paste();
                break;
            case SDL_SCANCODE_A:
                {
                    cout << "You are altering " << selected->id << endl;
                    cout << "-----" << endl;
                    cout << "What would you like to alter?" << endl;
                    while (true){
                        string option;
                        string setTo;
                        cin >> option;
                        if(option == "visible") {
                            cin >> setTo;
                            if (setTo == "true") {
                                selected->visible = true;
                            }
                            else if (setTo == "false") {
                                selected->visible = false;
                            }
                            else {
                                cout << "Exiting visible." << endl;
                            }
                        }
                        else if(option == "position") {
                            cout << "Current position is " << selected->position.x << ", " << selected->position.y << endl;
                            int posX, posY;
                            while (true){
                                cout << "Enter x" << endl;
                                cin >> setTo;
                                try {
                                    posX = stoi(setTo);
                                    break;
                                }
                                catch (invalid_argument const &e) {
                                    cout << "Not an int. Try again." << endl;
                                }
                            }
                            while (true){
                                cout << "Enter y" << endl;
                                cin >> setTo;
                                try {
                                    posY = stoi(setTo);
                                    break;
                                }
                                catch (invalid_argument const &e) {
                                    cout << "Not an int. Try again." << endl;
                                }
                            }
                            SDL_Point pos = {posX, posY};
                            selected->position = pos;
                        }
                        else if (option == "width") {
                            cout << "Current width is " << selected->width << endl;
                            int w;
                            while (true){
                                cout << "Enter width" << endl;
                                cin >> setTo;
                                try {
                                    w = stoi(setTo);
                                    break;
                                }
                                catch (invalid_argument const &e) {
                                    cout << "Not an int. Try again." << endl;
                                }
                            }
                            selected->width = w;
                        }
                        else if (option == "height") {
                            cout << "Current height is " << selected->height << endl;
                            int h;
                            while (true){
                                cout << "Enter height" << endl;
                                cin >> setTo;
                                try {
                                    h = stoi(setTo);
                                    break;
                                }
                                catch (invalid_argument const &e) {
                                    cout << "Not an int. Try again." << endl;
                                }
                            }
                            selected->height = h;
                        }
                        else if (option == "pivot") {
                            cout << "Current pivot is " << selected->pivot.x << ", " << selected->pivot.y << endl;
                            int posX, posY;
                            while (true){
                                cout << "Enter x" << endl;
                                cin >> setTo;
                                try {
                                    posX = stoi(setTo);
                                    break;
                                }
                                catch (invalid_argument const &e) {
                                    cout << "Not an int. Try again." << endl;
                                }
                            }
                            while (true){
                                cout << "Enter y" << endl;
                                cin >> setTo;
                                try {
                                    posY = stoi(setTo);
                                    break;
                                }
                                catch (invalid_argument const &e) {
                                    cout << "Not an int. Try again." << endl;
                                }
                            }
                            SDL_Point pos = {posX, posY};
                            selected->pivot = pos;
                        }
                        else if (option == "scaleX") {
                            cout << "Current scaleX is " << selected->scaleX << endl;
                            int scale;
                            while (true){
                                cout << "Enter scale" << endl;
                                cin >> setTo;
                                try {
                                    scale = stod(setTo);
                                    break;
                                }
                                catch (invalid_argument const &e) {
                                    cout << "Not a double. Try again." << endl;
                                }
                            }
                            selected->scaleX = scale;
                        }
                        else if (option == "scaleY") {
                            cout << "Current scaleY is " << selected->scaleY << endl;
                            int scale;
                            while (true){
                                cout << "Enter scale" << endl;
                                cin >> setTo;
                                try {
                                    scale = stod(setTo);
                                    break;
                                }
                                catch (invalid_argument const &e) {
                                    cout << "Not a double. Try again." << endl;
                                }
                            }
                            selected->scaleY = scale;
                        }
                        else if (option == "rotation") {
                            cout << "Current rotation is " << selected->rotation << endl;
                            int rot;
                            while (true){
                                cout << "Enter radian value" << endl;
                                cin >> setTo;
                                try {
                                    rot = stod(setTo);
                                    break;
                                }
                                catch (invalid_argument const &e) {
                                    cout << "Not a double. Try again." << endl;
                                }
                            }
                            selected->rotation = rot;
                        }
                        else if (option == "alpha") {
                            cout << "Current alpha is " << selected->alpha << endl;
                            int alp;
                            while (true){
                                cout << "Enter alpha value" << endl;
                                cin >> setTo;
                                try {
                                    alp = stoi(setTo);
                                    break;
                                }
                                catch (invalid_argument const &e) {
                                    cout << "Not an int. Try again." << endl;
                                }
                            }
                            selected->alpha = alp;
                        }
                        else if (option == "facingRight") {
                            cout << "Current facingRight is" << selected->facingRight << endl;
                            cin >> setTo;
                            if (setTo == "true") {
                                selected->facingRight = true;
                            }
                            else if (setTo == "false") {
                                selected->facingRight = false;
                            }
                            else {
                                cout << "Exiting facingRight." << endl;
                            }
                        }
                        else if (option == "id") {
                            cout << "Current id is " << selected->id << endl;
                            cin >> setTo;
                            selected->id = setTo;
                            cout << "Its new name is " << setTo << endl;
                        }
                        else if (option == "q" || option == "quit") {
                            cout << "bye bye !" << endl;
                            break;
                        }
                        else {
                            cout << "We don't have an option for that..." << endl;
                        }
                    cout << "Anything else?" << endl;
                    }
                    break;
                }
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
            case SDL_SCANCODE_Z:
                {
                    cout << "Clear the scene?" << endl;
                    string uInp;
                    cin >> uInp;
                    if (uInp == "y") {
                        for(int i = sceneWindow->children.size() - 1; i > -1; i--) {
                            sceneWindow->removeChild(i);
                        }
                    }
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
	Game::update(pressedKeys, controllerInput);
}

void DevTool::draw(AffineTransform &at){ //have to remove selection box before saving then add it back in after
 //    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
 //    SDL_RenderClear(Game::renderer);
 //    DevTool::drawGrid();
	// DisplayObjectContainer::draw(at);
	// SDL_RenderPresent(Game::renderer);
    Game::draw(at);
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
