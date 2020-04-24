#include "CollisionSystem.h"
#include "DisplayObject.h"
#include "DisplayObjectEvent.h"
#include <iostream>
#include "Player.h"
using namespace std;

CollisionSystem::CollisionSystem(){
	typeMap = unordered_map<string, vector<DisplayObject*>>();
	collisionPairs = vector<pair<string, string>>();
}

CollisionSystem::~CollisionSystem(){

}
void CollisionSystem::clearAllData(){
	typeMap.clear();
	collisionPairs.clear();
}
//checks collisions between pairs of DOs where the corresponding types have been requested
//to be checked (via a single call to watchForCollisions) below.
void CollisionSystem::update(){
	// iterate over colllision pairs
	for (auto pair=collisionPairs.begin(); pair != collisionPairs.end(); ++pair) {
		// check for collisions between the elements in each vector
		for (auto doType1=typeMap.at(pair->first).begin(); doType1 != typeMap.at(pair->first).end(); ++doType1) {

			for (auto doType2=typeMap.at(pair->second).begin(); doType2 != typeMap.at(pair->second).end(); ++doType2) {
				
				// check if anything has changed since last time
				SDL_Point prevPos1 = prevMap.at(*doType1);
				SDL_Point prevPos2 = prevMap.at(*doType2);
				SDL_Point curPos1 = (*doType1)->getHitboxPts().topLeft;
				SDL_Point curPos2 = (*doType2)->getHitboxPts().topLeft;

				int xDelta1 = curPos1.x - prevPos1.x;
				int yDelta1 = curPos1.y - prevPos1.y;
				int xDelta2 = curPos2.x - prevPos2.x;
				int yDelta2 = curPos2.y - prevPos2.y;

				// cout << xDelta1 << endl;
				// cout << xDelta2 << endl;
				if ( (xDelta1 == 0) && (yDelta1 == 0) && (xDelta2 == 0) && (yDelta2 == 0)  ){
					// if no change skip
					// cout << "SKIPPING" << endl;
					continue;
				}

				// if(DisplayObject::distance(curPos1, curPos2) > 100){
				// 	// cout << "SKIPPING" << endl;
				// 	continue;
				// }

				if (collidesWith(*doType1, *doType2)){
					// cout << "HEY" << endl;
					//cout << (*doType1)->gameType << " object collided with a " << (*doType2)->gameType << " object. " << rand() << endl;
					//(*doType1)->onCollision(*doType2); 
					// (*doType2)->onCollision(*doType1);
					resolveCollision(*doType2,*doType1, xDelta1, yDelta1, xDelta2, yDelta2);
				}
			}
		}
	}

	// update previous Hitbox point
	for (auto object=prevMap.begin(); object != prevMap.end(); ++object){
		object->second = object->first->getHitboxPts().topLeft;
	}

	
}

//This system watches the game's display tree and is notified whenever a display object is placed onto
//or taken off of the tree. Thus, the collision system always knows what DOs are in the game at any moment automatically.
void CollisionSystem::handleEvent(Event* e){
	if (e->getType() == DO_ADDED_EVENT){
		DisplayObjectEvent* doEvent = (DisplayObjectEvent*) e;
		DisplayObject* displayObject = doEvent->displayObject;
		// check if gameType is not already in map
		if (typeMap.find(displayObject->gameType) == typeMap.end()){
			// if not go ahead and insert new vector with element
			vector<DisplayObject*> newList = vector<DisplayObject*>();
			newList.push_back(displayObject);
			typeMap.insert({displayObject->gameType, newList});
		} else {
			// if already present insert into existing vector
			typeMap.at(displayObject->gameType).push_back(displayObject);
		}
		// put in prev map to keep track of previous point
		if (prevMap.find(displayObject) == prevMap.end()){
			prevMap.insert({displayObject, displayObject->getHitboxPts().topLeft});
		}
	}
}

//This function asks the collision system to start checking for collisions between all pairs
//of DOs of a given type (e.g., player vs platform). The system will begin to check all player objects
//against all platform objects that are in the current scene.
void CollisionSystem::watchForCollisions(string type1, string type2){
    this->collisionPairs.emplace_back(type1, type2);
}

//returns true iff obj1 hitbox and obj2 hitbox overlap. Uses the following method from DO:
//	SDL_Point* DisplayObject::getGlobalHitbox();
bool CollisionSystem::collidesWith(DisplayObject* obj1, DisplayObject* obj2){
    // get points for hitbox1 in global coordinate system
	HitboxPoints pts1 = obj1->getHitboxPts();

	// lines from those points
	Line l1 = {pts1.topLeft, pts1.topRight};
	Line l2 = {pts1.topRight, pts1.bottomRight};
	Line l3 = {pts1.bottomLeft, pts1.bottomRight};
	Line l4 = {pts1.topLeft, pts1.bottomLeft};

	Line displayObjectLines1[4] = {l1, l2, l3, l4};

	// get points for hitbox2 in global coordinate system
	HitboxPoints pts2 = obj2->getHitboxPts();

	// lines from those points
	Line l5 = {pts2.topLeft, pts2.topRight};
	Line l6 = {pts2.topRight, pts2.bottomRight};
	Line l7 = {pts2.bottomLeft, pts2.bottomRight};
	Line l8 = {pts2.topLeft, pts2.bottomLeft};

	Line displayObjectLines2[4] = {l5, l6, l7, l8};

	// see if any line intersects
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			// cout << "i: " << i << " j: " << j << endl;
			// if any line intersects there is a collision
			if ( intersects(displayObjectLines1[i], displayObjectLines2[j]) ){
				return true;
			}
		}
	}
	// if no intersections but one point is inside another hitbox there is also a collision
	if ( checkInside(pts1, pts2.topLeft) || checkInside(pts2, pts1.topLeft) ){
		return true;
	}
	return false;
}

//Resolves the collision that occurred between d and other
//xDelta1 and yDelta1 are the amount d moved before causing the collision.
//xDelta2 and yDelta2 are the amount other moved before causing the collision.
void CollisionSystem::resolveCollision(DisplayObject* other, DisplayObject* d, int xDelta1, int yDelta1, int xDelta2, int yDelta2){
	//if mvmt > 0, then DO that moved position - mvmt, change back to old position
	//checking that object moved 	
	if (d->onCollision(other) || other->onCollision(d)){
		return;
	}

	// check if collision in y direction
	// d->position.x -= xDelta1; 
	// bool yCol = collidesWith(d, other); 
	// d->position.x += xDelta1;

	// // check if collision in x direction
	// d->position.y -= yDelta1; 
	// bool xCol = collidesWith(d, other); 
	// d->position.y += yDelta1;

	// if (xCol) {
	// 	d->position.x -=xDelta1; 
	// }
	// if (yCol) {
	// 	d->position.y -=yDelta1; 
	// }
	// if (!xCol && !yCol) {
	// 	d->position.x -= xDelta1; 
	// 	d->position.y -= yDelta1; 
	// }

	// binary search
	// int maxDelta = max(xDelta1, max(yDelta1, max(xDelta2, yDelta2)));
	// for (int i = (int) log2(maxDelta) + 1; i > 0; i--){
	// 	xDelta1 = lround(xDelta1 / 2.0);
	// 	yDelta1 = lround(yDelta1 / 2.0);
	// 	xDelta2 = lround(xDelta2 / 2.0);
	// 	yDelta2 = lround(yDelta2 / 2.0);
	// 	if (collidesWith(d, other)){
	// 		d->position.x -= xDelta1;
	// 		d->position.y -= yDelta1;  
	// 	}
	// 	else {
	// 		d->position.x += xDelta1;
	// 		d->position.y += yDelta1; 
	// 	}
	// }
	// // if collides with on final move, move back
	// if (collidesWith(d, other)){
	// 	d->position.x -= xDelta1;
	// 	d->position.y -= yDelta1;  
	// }

	d->position.x -= xDelta1; 
	bool yCol = collidesWith(d, other); 
	d->position.x += xDelta1;

	// check if collision in x direction
	d->position.y -= yDelta1; 
	bool xCol = collidesWith(d, other); 
	d->position.y += yDelta1;
	//yDelta1 = 0;

	int maxDelta;
	if (xCol) {
		// binary search with x
		maxDelta = max(xDelta1, xDelta2);
		for (int i = (int) log2(maxDelta) + 1; i > 0; i--){
			xDelta1 = lround(xDelta1 / 2.0);
			xDelta2 = lround(xDelta2 / 2.0);
			if (collidesWith(d, other)){
				d->position.x -= xDelta1;  
			}
			else {
				d->position.x += xDelta1;
			}
		}
		if (collidesWith(d, other)){
			d->position.x -= xDelta1;  
		}
	}
	if (yCol) {
		// binary search with y
		maxDelta = max(yDelta1, yDelta2);
		for (int i = (int) log2(maxDelta) + 1; i > 0; i--){
			yDelta1 = lround(yDelta1 / 2.0);
			yDelta2 = lround(yDelta2 / 2.0);
			if (collidesWith(d, other)){
				d->position.y -= yDelta1;  
			}
			else {
				d->position.y += yDelta1;
			}
		}
		if (collidesWith(d, other)){
			d->position.y -= yDelta1;  
		}
	}
	if (!xCol && !yCol) {
		// binary search with both
		maxDelta = max(xDelta1, max(yDelta1, max(xDelta2, yDelta2)));
		for (int i = (int) log2(maxDelta) + 1; i > 0; i--){
			xDelta1 = lround(xDelta1 / 2.0);
			yDelta1 = lround(yDelta1 / 2.0);
			xDelta2 = lround(xDelta2 / 2.0);
			yDelta2 = lround(yDelta2 / 2.0);
			if (collidesWith(d, other)){
				d->position.x -= xDelta1;
				d->position.y -= yDelta1;  
			}
			else {
				d->position.x += xDelta1;
				d->position.y += yDelta1; 
			}
		}
		// if collides with on final move, move back
		if (collidesWith(d, other)){
			d->position.x -= xDelta1;
			d->position.y -= yDelta1;  
		}
	}
}


// private helper method
bool CollisionSystem::intersects(Line l1, Line l2) {
	// get orientations
	SDL_Point p1 = l1.pt1;
	SDL_Point p2 = l1.pt2;
	SDL_Point q1 = l2.pt1;
	SDL_Point q2 = l2.pt2;

	int o1 = getOrientation(p1, p2, q1);
	int o2 = getOrientation(p1, p2, q2);
	int o3 = getOrientation(q1, q2, p1);
	int o4 = getOrientation(q1, q2, p2);
	// if one orientation is the same then there is no intersection
	if ( o1 != o2  && o3 != o4 ){
		return true;
	// check if colinear
	} else if ((o1 == 0) && (o2 == 0) && (o3 == 0) && (o4 == 0)){
		if ((p1.x >= q1.x && p1.x <= q2.x || p1.x <= q1.x && p1.x >= q2.x || p2.x >= q1.x && p2.x <= q2.x || p2.x <= q1.x && p2.x >= q2.x) && (p1.y >= q1.y && p1.y <= q2.y || p1.y <= q1.y && p1.y >= q2.y || p2.y >= q1.y && p2.y <= q2.y || p2.y <= q1.y && p2.y >= q2.y)) {
			return true;
		} 
	} 
	return false;
}

int CollisionSystem::getOrientation(SDL_Point p1, SDL_Point p2, SDL_Point p3) {
	int s1;
	int s2;

	s1 = (p3.y - p1.y) * (p2.x - p3.x) - (p3.x - p1.x) * (p2.y - p3.y);
	s2 = 0;

	if (s1 < s2){
		// turns left
		return -1;
	} else if (s2 < s1) {
		// turns right
		return 1;
	} else {
		// collinear
		return 0;
	}
}

bool CollisionSystem::checkInside(HitboxPoints pts, SDL_Point pt){
	// get pixel area of hitbox
	int area = abs(pts.topLeft.x * (pts.topRight.y - pts.bottomLeft.y) + pts.topRight.x * (pts.bottomLeft.y - pts.topLeft.y) + pts.bottomLeft.x * (pts.topLeft.y - pts.topRight.y));

	int sum = 0;
	// make triangle out of corners and pt
	Line l1 = {pts.topLeft, pts.topRight};
	Line l2 = {pts.topRight, pts.bottomRight};
	Line l3 = {pts.bottomLeft, pts.bottomRight};
	Line l4 = {pts.topLeft, pts.bottomLeft};

	// add to sum
	Line lines[4] = {l1, l2, l3, l4};
	for (int i = 0; i < 4; i++){
		sum += abs(lines[i].pt1.x * (lines[i].pt2.y - pt.y) + lines[i].pt2.x * (pt.y-lines[i].pt1.y) + pt.x * (lines[i].pt1.y - lines[i].pt2.y));
	}

	if (sum != (2 * area)){
		return false;
	}
	return true;
}