#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "DisplayObject.h"
#include "MyGame.h"


using namespace std;

int main( int argc, char* args[] )
{
	MyGame* game = new MyGame();
	//Start up SDL and create window
	if( !game->init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !game->loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//The dot that will be moving around on the screen
			DisplayObject character;

			//The camera area
			SDL_Rect camera = { 0, 0, game->SCREEN_WIDTH, game->SCREEN_HEIGHT };

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

					//Handle input for the dot
					character.handleEvent( e );
				}

				//Move the dot
				character.move();

				//Center the camera over the dot
				camera.x = ( character.getPosX() + DisplayObject::DOT_WIDTH / 2 ) - game->SCREEN_WIDTH / 2;
				camera.y = ( character.getPosY() + DisplayObject::DOT_HEIGHT / 2 ) - game->SCREEN_HEIGHT / 2;

				//Keep the camera in bounds
				if( camera.x < 0 )
				{ 
					camera.x = 0;
				}
				if( camera.y < 0 )
				{
					camera.y = 0;
				}
				if( camera.x > game->LEVEL_WIDTH - camera.w )
				{
					camera.x = game->LEVEL_WIDTH - camera.w;
				}
				if( camera.y > game->LEVEL_HEIGHT - camera.h )
				{
					camera.y = game->LEVEL_HEIGHT - camera.h;
				}

				//Clear screen
				SDL_SetRenderDrawColor( game->gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( game->gRenderer );

				//Render background
				game->gBGTexture.render( 0, 0, &camera );

				//Render objects
				character.render( camera.x, camera.y , game->gDotTexture);

				//Update screen
				SDL_RenderPresent( game->gRenderer );
			}
		}
	}

	//Free resources and close SDL
	game->close();

	return 0;
}