#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Game.h"
#include "MyGame.h"
<<<<<<< HEAD
=======
#include "Scene.h"
>>>>>>> 044140141e47a9b39aa5af7fc4b27db617a787ce
#include "LTexture.h"


using namespace std;

bool MyGame::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

//Loads media
bool MyGame::loadMedia(){
	//Loading success flag
	bool success = true;

<<<<<<< HEAD
	//Load dot texture
	if( !gDotTexture.loadFromFile( "/Users/apple/Desktop/experiment/resources/solarSystem/Moon.png", gRenderer ) )
=======
	//Load PNG texture
	gDotTexture = loadTexture( "resources/solarSystem/Moon.png" );
	if( gDotTexture == NULL )
>>>>>>> 044140141e47a9b39aa5af7fc4b27db617a787ce
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}

	//Load background texture
	if( !gBGTexture.loadFromFile( "/Users/apple/Desktop/experiment/resources/bg.png" , gRenderer) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	// Scene* scene1 = new Scene(); 
	// scene1->loadScene("resources/scenes/scene1.json");

	return success;
}

//Frees media and shuts down SDL
void MyGame::close(){
<<<<<<< HEAD
	//Free loaded images
	gDotTexture.free();
	gBGTexture.free();
=======
	//Free loaded image
	SDL_DestroyTexture( gDotTexture );
	gDotTexture = NULL;
>>>>>>> 044140141e47a9b39aa5af7fc4b27db617a787ce

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

// //Loads individual image as texture
// SDL_Texture* MyGame::loadTexture( std::string path ){
// 	//The final texture
// 	SDL_Texture* newTexture = NULL;

// 	//Load image at specified path
// 	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
// 	if( loadedSurface == NULL )
// 	{
// 		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
// 	}
// 	else
// 	{
// 		//Create texture from surface pixels
//         newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
// 		if( newTexture == NULL )
// 		{
// 			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
// 		}

// 		//Get rid of old loaded surface
// 		SDL_FreeSurface( loadedSurface );
// 	}

// 	return newTexture;
// }