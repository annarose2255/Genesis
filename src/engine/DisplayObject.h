#ifndef DISPLAYOBJECT_H
#define DISPLAYOBJECT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <set>
#include "AffineTransform.h"
#include <string>
#include <fstream>

using namespace std;

struct HitboxPoints {
	SDL_Point topLeft;
	SDL_Point topRight;
	SDL_Point bottomLeft;
	SDL_Point bottomRight;
};

struct Line {
	SDL_Point pt1;
	SDL_Point pt2;
};

class DisplayObject{


public:

	struct Hitbox {
		// top left point
		SDL_Point origin = {0, 0};
		int width = 100;
		int height = 100;
	};

	string id = "DEFAULT_ID";
	string imgPath = "";
	int red, green, blue;
	string type = "DisplayObject";
	string gameType = "";

	DisplayObject* parent = NULL;

	bool isRGB = false;

	DisplayObject();
	DisplayObject(string id, string path);
	DisplayObject(string id, int red, int green, int blue);
	virtual ~DisplayObject();
	
	virtual void update(set<SDL_Scancode> pressedKeys, set<SDL_GameControllerButton> pressedButtons);
	virtual void draw(AffineTransform &at);

	SDL_Rect doCam; //camera for display object
	SDL_Rect collider;
	bool checkCollision(SDL_Rect a, SDL_Rect b);

	void loadTexture(string filepath);
	void loadRGBTexture(int red, int green, int blue);
	void setTexture(SDL_Texture* t);

	void applyTransformations(AffineTransform &at);
	void reverseTransformations(AffineTransform &at);

	AffineTransform *globalTransform();

	int getWidth();
	int getHeight();
	HitboxPoints getHitboxPts();
	// Line** getHitboxLines();
	void setHitbox(SDL_Point origin, int width, int height);
	void drawHitbox();

	void setScrollSpeed(double speed);
	bool visible = true;
	SDL_Point position = {0, 0};
	SDL_Point pos2;
	double scrollSpeed;
	int width = 100;
	int height = 100;
	SDL_Point pivot = {0, 0};
	double scaleX = 1.0;
	double scaleY = 1.0;
	double rotation = 0.0; // in radians
	int alpha = 255;
	bool facingRight = true;
    bool isSheet = false;
	bool camPerspective = true;
    SDL_Rect srcrect;
	SDL_Rect dstrect;
	// Camera * cam;
	// SDL_Rect camera = { 0, 0, 800, 700 };
	SDL_Texture* curTexture;
	Hitbox hitbox;
	static double distance(SDL_Point &p1, SDL_Point &p2);
	
private:
	
	double calculateRotation(SDL_Point &origin, SDL_Point &p);
	
	SDL_Texture* texture = NULL;
	SDL_Surface* image = NULL;

	/* Texture currently being drawn. Equal to texture for normal DO */

};

#endif
