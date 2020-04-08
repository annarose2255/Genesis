#include "CollisionSystem.h"
#include "DisplayObject.h"
#include <iostream>

using namespace std;

CollisionSystem::CollisionSystem(){
	typeMap = unordered_map<string, vector<DisplayObject*>>();
	collisionPairs = vector<pair<string, string>>();
}

CollisionSystem::~CollisionSystem(){

}

//checks collisions between pairs of DOs where the corresponding types have been requested
//to be checked (via a single call to watchForCollisions) below.
void CollisionSystem::update(){
	// iterate over colllision pairs
	for (auto pair=collisionPairs.begin(); pair != collisionPairs.end(); ++pair) {
		// check for collisions between the elements in each vector
		for (auto doType1=typeMap.at(pair->first).begin(); doType1 != typeMap.at(pair->first).end(); ++doType1) {
			for (auto doType2=typeMap.at(pair->second).begin(); doType2 != typeMap.at(pair->second).end(); ++doType2) {
				if (collidesWith(*doType1, *doType2)){
					cout << (*doType1)->gameType << " object collided with a " << (*doType2)->gameType << " object. " << rand() << endl;
				}
			}
		}
	} 
}

//This system watches the game's display tree and is notified whenever a display object is placed onto
//or taken off of the tree. Thus, the collision system always knows what DOs are in the game at any moment automatically.
void CollisionSystem::handleEvent(Event* e){
	if (e->getType() == DO_ADDED_EVENT){
		cout << "DISPLAY OBJECT ADDED"  << endl;
		DisplayObject* displayObject = (DisplayObject*) e->getData("displayObject");
		// check if gameType is not already in map
		if (typeMap.find(displayObject->gameType) == typeMap.end()){
			cout << "Object gameType is new: " << displayObject->gameType  << endl;
			// if not go ahead and insert new vector with element
			vector<DisplayObject*> newList = vector<DisplayObject*>();
			newList.push_back(displayObject);
			typeMap.insert({displayObject->gameType, newList});
		} else {
			// if already present insert into existing vector
			cout << "Object gameType is NOT new" << displayObject->gameType  << endl;
			typeMap.at(displayObject->gameType).push_back(displayObject);
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
	// AffineTransform gT1 = *obj1->globalTransform();
	// SDL_Point topLeft1 = gT1.transformPoint(0, 0);
	// SDL_Point topRight1 = gT1.transformPoint(obj1->hitbox.width, 0);
	// SDL_Point bottomRight1 = gT1.transformPoint(obj1->hitbox.width, obj1->hitbox.height);
	// SDL_Point bottomLeft1 = gT1.transformPoint(obj1->hitbox.width, 0);

	// lines from those points
	// Line l1 = {topLeft1, topRight1};
	// Line l2 = {topRight1, bottomRight1};
	// Line l3 = {bottomLeft1, bottomRight1};
	// Line l4 = {topLeft1, bottomLeft1};
	Line l1 = {pts1.topLeft, pts1.topRight};
	Line l2 = {pts1.topRight, pts1.bottomRight};
	Line l3 = {pts1.bottomLeft, pts1.bottomRight};
	Line l4 = {pts1.topLeft, pts1.topRight};

	Line displayObjectLines1[4] = {l1, l2, l3, l4};

	// get points for hitbox2 in global coordinate system
	HitboxPoints pts2 = obj2->getHitboxPts();
	// AffineTransform gT2 = *obj2->globalTransform();
	// SDL_Point topLeft2 = gT2.transformPoint(0, 0);
	// SDL_Point topRight2 = gT2.transformPoint(obj2->hitbox.width, 0);
	// SDL_Point bottomRight2 = gT2.transformPoint(obj2->hitbox.width, obj2->hitbox.height);
	// SDL_Point bottomLeft2 = gT2.transformPoint(obj2->hitbox.width, 0);

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
void CollisionSystem::resolveCollision(DisplayObject* d, DisplayObject* other, int xDelta1, int yDelta1, int xDelta2, int yDelta2){

}


// private helper method
bool CollisionSystem::intersects(Line l1, Line l2) {
	// get orientations
	SDL_Point p1 = l1.pt1;
	SDL_Point q1 = l1.pt2;
	SDL_Point p2 = l2.pt1;
	SDL_Point q2 = l2.pt2;
	// cout << "O1" << endl;
	int o1 = getOrientation(p1, q1, p2);
	// cout << "O2" << endl;
	int o2 = getOrientation(p1, q1, q2);
	// cout << "O3" << endl;
	int o3 = getOrientation(p2, q2, p1);
	// cout << "O4" << endl;
	int o4 = getOrientation(p2, q2, q1);
	// if one orientation is the same then there is no intersection
	if ( o1 != o2  && o3 != o4 ){
		// cout << "HERE" << endl;
		// cout << "o1 " << o1 << " o2 " << o2 << " o3 " << o3 << " o4 " << o4 << endl;
		return true;
	// check if colinear
	} else if ((o1 == 0) && (o2 == 0) && (o3 == 0) && (o4 == 0)){
		// check if one point is inbetween two other points using x projection
		// sort x values of one line
		int smallerX = p1.x;
		int largerX = q1.x;
		if (q1.x < smallerX){
			smallerX = q1.x;
			largerX = p1.x;
		}
		// same thing for y
		// int smallerY = p1.y;
		// int largerY = q1.y;
		// if (q1.y < smallerY){
		// 	smallerY = q1.y;
		// 	largerY = p1.y;
		// }
		// see if either of the other line's points fall in between
		if ( (p2.x >= smallerX && p2.x <= largerX) || (q2.x >= smallerX && q2.x <= largerX) ){
			return true;
		}
	} 
	return false;
}

int CollisionSystem::getOrientation(SDL_Point p1, SDL_Point p2, SDL_Point p3) {
	float s1;
	float s2;
	// if (q1.x - p1.x == 0){
	// 	s1 = 0;
	// } else {
	// 	s1 = (q1.y - p1.y) / (q1.x - p1.x);
	// }
	// if (p2.x - q1.x == 0){
	// 	s2 = 0;
	// } else {
	// 	cout << "p2.y: " << p2.y << " q1.y " << q1.y << " p2.x " << p2.x << " q1.x " << q1.x << endl;
	// 	s2 = (p2.y - q1.y) / (p2.x - q1.x);
	// }
	// cout << "s1: " << s1 << " s2: " << s2 << endl;
	// if (s1 < s2){
	// 	// turns left
	// 	return -1;
	// } else if (s2 < s1) {
	// 	// turns right
	// 	return 1;
	// } else {
	// 	// collinear
	// 	return 0;
	// }

	// s1 = atan2(p2.y - p1.y, p2.x - p1.x);
	// s2 = atan2(p3.y - p1.y, p3.x - p1.x);
	s1 = (p3.y - p1.y) * (p2.x - p3.x) - (p3.x - p1.x) * (p2.y - p3.y);
	s2 = 0;

	// cout << " P1: (" << p1.x << "," << p1.y << ")" << " P2: (" << p2.x << "," << p2.y << ")" << " P3: (" << p3.x << "," << p3.y << ")" << endl;
	// if (p2.x - p1.x == 0){
	// 	cout << "UNDEFINED" << endl;
	// 	s1 = 0;
	// } else {
	// 	s1 = (float)(p2.y - p1.y) / (float)(p2.x - p1.x);
	// }
	// if (p3.x - p1.x == 0){
	// 	cout << "UNDEFINED" << endl;
	// 	s2 = 0;
	// } else {
	// 	cout << "p3.y: " << p3.y << " p1.y " << p1.y << " p3.x " << p3.x << " p1.x " << p1.x << endl;
	// 	s2 = (float)(p3.y - p1.y) / (float)(p3.x - p1.x);
	// }
	// cout << "s1: " << s1 << " s2: " << s2 << endl;
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
	// int width = abs(pts.topRight.x - pts.topLeft.x);
	// cout << "W: " << width << endl;
	// int height = abs(pts.bottomLeft.y - pts.topLeft.y);
	// cout << "H: " << height << endl;
	// int area = width * height;
	int sum = 0;
	// make triangle out of corners and pt
	Line l1 = {pts.topLeft, pts.topRight};
	Line l2 = {pts.topRight, pts.bottomRight};
	Line l3 = {pts.bottomLeft, pts.bottomRight};
	Line l4 = {pts.topLeft, pts.bottomLeft};
	// x1 = lines[i].pt1.x
	// y1 = lines[i].pt1.y
	// x2 = lines[i].pt2.x
	// y2 = lines[i].pt2.y
	// x3 = pt.x
	// y3 = pt.y
	
	// abs(0.5*(x1*(y2-y3)+x2*(y3-y1)+x3*(y1-y2)))
	// get area of triangle

	// add to sum
	Line lines[4] = {l1, l2, l3, l4};
	for (int i = 0; i < 4; i++){
		sum += abs(lines[i].pt1.x * (lines[i].pt2.y - pt.y) + lines[i].pt2.x * (pt.y-lines[i].pt1.y) + pt.x * (lines[i].pt1.y - lines[i].pt2.y));
	}
	// check if equal
	// cout << "SUM: " << sum << endl;
	// cout << "AREA: " << 2 * area << endl;
	if (sum != (2 * area)){
		return false;
	}
	return true;
}