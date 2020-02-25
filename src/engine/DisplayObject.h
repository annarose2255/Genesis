#ifndef DISPLAYOBJECT_H
#define DISPLAYOBJECT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "LTexture.h"

class DisplayObject{

   public:
        LTexture gDotTexture;
        
        //The dimensions of the level
        const int LEVEL_WIDTH = 1280;
        const int LEVEL_HEIGHT = 960;

		//The dimensions of the dot
		static const int DOT_WIDTH = 20;
		static const int DOT_HEIGHT = 20;


		//Maximum axis velocity of the dot
		static const int DOT_VEL = 10;

		//Initializes the variables
		DisplayObject();

		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event& e );

		//Moves the dot
		void move();

		//Shows the dot on the screen relative to the camera
		void render( int camX, int camY );

		//Position accessors
		int getPosX();
		int getPosY();

    private:
		//The X and Y offsets of the dot
		int mPosX, mPosY;

		//The velocity of the dot
		int mVelX, mVelY;
};

#endif