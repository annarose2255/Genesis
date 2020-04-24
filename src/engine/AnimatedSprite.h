#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "Sprite.h"
#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <rapidxml.hpp>

using namespace std;
using namespace rapidxml;

struct Frame {
	SDL_Surface* image;
	SDL_Texture* texture;
};

struct Animation {
	Frame** frames;
	string animName;
	string filepath;
    int numFrames;
	int frameRate;
	bool loop;
	int curFrame;
};

struct SSAnimation {
	SDL_Surface* image;
	SDL_Texture* texture;
    vector<SDL_Rect> frames;
    string animName;
    string filepath;
    int numFrames;
    int frameRate;
    bool loop;
    int curFrame;
};

class AnimatedSprite : public Sprite{

public:
	
	AnimatedSprite();
	AnimatedSprite(string id);
	AnimatedSprite(string id, bool isSheet);
	~AnimatedSprite();

	void addAnimation(string basepath, string animName, int numFrames, int frameRate, bool loop);
	void addSSAnimation(string spriteSheetPath, string xmlPath, int frameRate, bool loop);
	Animation* getAnimation(string animName);
    SSAnimation* getSSAnimation(string animName);

	void play(string animName);
	void replay();
	void stop();

	virtual void update(set<SDL_Scancode> pressedKeys, set<SDL_GameControllerButton> pressedButtons, set<pair<SDL_GameControllerAxis, float>> movedAxis);
	virtual void draw(AffineTransform &at);
	void setState(string newstate);
	bool playing = false;

    vector<string> animationNames;    
	string state;
private:
	string process(string file);
    
    Animation* current;
    SSAnimation* sscurrent;
	vector<Animation*> animations;
    vector<SSAnimation*> ssanimations;
	int frameCount;
};

#endif
