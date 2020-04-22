#include "SDL2/SDL_mixer.h"
#ifndef SOUND_H
#define SOUND_H

class Sound{ 

public:
	Sound();
	~Sound();

	void playSFX();
	void playMusic();
	void pauseMusic();
	void resumeMusic();
private:
	bool success = true;
	Mix_Music *gMusic = NULL;

	
};

#endif