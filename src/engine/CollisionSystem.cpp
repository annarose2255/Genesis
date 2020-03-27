#include "CollisionSystem.h"

CollisionSystem::CollisionSystem(){

}

CollisionSystem::~CollisionSystem(){

}

//checks collisions between pairs of DOs where the corresponding types have been requested
//to be checked (via a single call to watchForCollisions) below.
void CollisionSystem::update(){

}

//This system watches the game's display tree and is notified whenever a display object is placed onto
//or taken off of the tree. Thus, the collision system always knows what DOs are in the game at any moment automatically.
void CollisionSystem::handleEvent(Event* e){

}

//This function asks the collision system to start checking for collisions between all pairs
//of DOs of a given type (e.g., player vs platform). The system will begin to check all player objects
//against all platform objects that are in the current scene.
void CollisionSystem::watchForCollisions(string type1, string type2){
    
}

//returns true iff obj1 hitbox and obj2 hitbox overlap. Uses the following method from DO:
//	SDL_Point* DisplayObject::getGlobalHitbox();
bool CollisionSystem::collidesWith(DisplayObject* obj1, DisplayObject* obj2){
    // get points for hitbox1 in global coordinate system
	AffineTransform gT1 = obj1->globalTransform();
	SDL_Point topLeft1 = gT1.transformPoint(0, 0);
	SDL_Point topRight1 = gT1.transformPoint(obj1->hitbox.width, 0);
	SDL_Point bottomRight1 = gT1.transformPoint(obj1->hitbox.width, obj1->hitbox.height);
	SDL_Point bottomLeft1 = gT1.transformPoint(obj1->hitbox.width, 0);

	// lines from those points
	Line l1 = {topLeft1, topRight1};
	Line l2 = {topRight1, bottomRight1};
	Line l3 = {bottomLeft1, bottomRight1};
	Line l4 = {topLeft1, bottomLeft1};

	Line displayObjectLines1[4] = {l1, l2, l3, l4};

	// get points for hitbox2 in global coordinate system
	AffineTransform gT2 = obj2->globalTransform();
	SDL_Point topLeft2 = gT2.transformPoint(0, 0);
	SDL_Point topRight2 = gT2.transformPoint(obj2->hitbox.width, 0);
	SDL_Point bottomRight2 = gT2.transformPoint(obj2->hitbox.width, obj2->hitbox.height);
	SDL_Point bottomLeft2 = gT2.transformPoint(obj2->hitbox.width, 0);

	// lines from those points
	Line l5 = {topLeft2, topRight2};
	Line l6 = {topRight2, bottomRight2};
	Line l7 = {bottomLeft2, bottomRight2};
	Line l8 = {topLeft2, bottomLeft2};

	Line displayObjectLines2[4] = {l5, l6, l7, l8};

	// see if any line intersects
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			// if any line intersects there is a collision
			if ( intersects(displayObjectLines1[i], displayObjectLines2[j]) ){
				return true;
			}
		}
	}
	return false;
}

//Resolves the collision that occurred between d and other
//xDelta1 and yDelta1 are the amount d moved before causing the collision.
//xDelta2 and yDelta2 are the amount other moved before causing the collision.
void CollisionSystem::resolveCollision(DisplayObject* d, DisplayObject* other, int xDelta1, int yDelta1, int xDelta2, int yDelta2){

}


// private helper method
bool CollisionSystem::intersects(Line l1, Line l2) {
	// get orientations
	SDL_Point p1 = l1.pt1;
	SDL_Point q1 = l1.pt2;
	SDL_Point p2 = l2.pt1;
	SDL_Point q2 = l2.pt2;
	int o1 = getOrientation(p1, q1, p2);
	int o2 = getOrientation(p1, q1, q2);
	int o3 = getOrientation(p2, q2, p1);
	int o4 = getOrientation(p2, q2, q1);
	// if one orientation is the same then there is no intersection
	if ( o1 != o2  && o3 != o4 ){
		return true;
	// check if colinear
	} else if (o1 == 0 && o2 == 0 && o3 == 0 && o4 == 0){
		// check if one point is inbetween two other points using x projection
		// sort x values of one line
		int smallerX = p1.x;
		int largerX = q1.x;
		if (q1.x < smallerX){
			smallerX = q1.x;
			largerX = p1.x;
		}
		// see if either of the other line's points fall in between
		if ( (p2.x >= smallerX && p2.x <= largerX) || (q2.x >= smallerX && q2.x <= largerX) ){
			return true;
		}
	}
	return false;
}

int CollisionSystem::getOrientation(SDL_Point p1, SDL_Point q1, SDL_Point p2) {
	float s1 = (q1.y - p1.y) / (q1.x - p1.x);
	float s2 = (p2.y - q1.y) / (p2.x - q1.x);
	if (s1 < s2){
		// turns left
		return 1;
	} else if (s2 < s1) {
		// turns right
		return 2;
	} else {
		// collinear
		return 0;
	}
}