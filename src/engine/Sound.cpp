#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SDL2/SDL_mixer.h"
#include "Sound.h"
#include <string>

//https://lazyfoo.net/tutorials/SDL/21_sound_effects_and_music/index.php
Sound::Sound(){
    // Initialize SDL.
	// SDL_Init(SDL_INIT_AUDIO);
    if( SDL_Init( SDL_INIT_AUDIO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }

    //Initialize SDL_mixer 
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    //the mp3 format does not work --> have to conver the music to ogg format
    gMusic = Mix_LoadMUS( "game.ogg" );
    if( gMusic == NULL )
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

}
Sound::~Sound(){
    //Free the music
    Mix_FreeMusic( gMusic );
    gMusic = NULL;

}

void Sound::playSFX(){

}
void Sound::playMusic(){
    // gMusic = Mix_LoadMUS( "game.mp3" );
	// if( gMusic == NULL )
	// {
	// 	// printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
	// 	success = false;
	// }

    Mix_PlayMusic( gMusic, -1 );

}

//created another method to pause playing music
void Sound::pauseMusic(){
    Mix_PauseMusic();

}
//created another method to pause playing music
void Sound::resumeMusic(){
   Mix_ResumeMusic();

}