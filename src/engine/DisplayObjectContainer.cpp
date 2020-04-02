#include "DisplayObjectContainer.h"
#include "DisplayObject.h"
#include "AffineTransform.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;


DisplayObjectContainer::DisplayObjectContainer() : DisplayObject() {
    this->type = "DisplayObjectContainer";
}

DisplayObjectContainer::DisplayObjectContainer(string id, string filepath) : DisplayObject(id, filepath) {
    this->type = "DisplayObjectContainer";
}

DisplayObjectContainer::DisplayObjectContainer(string id, int red, int green, int blue) : DisplayObject(id, red, green, blue) {
    this->type = "DisplayObjectContainer";
}

DisplayObjectContainer::~DisplayObjectContainer() {
    for (int i = 0; i < children.size(); i++ ) {
        delete children[i];
        // children.erase(i)
    }
}

void DisplayObjectContainer::addChild(DisplayObject* child) {
    cout << "adding child" << endl;
    cout << "parent camPerspective: " << camPerspective << endl;
    child->camPerspective = camPerspective;
    children.push_back(child);
    child->parent = (DisplayObject *)this; // make sure to include reverse reference also
}

void DisplayObjectContainer::removeImmediateChild(DisplayObject* child) {
    for (int i = 0; i < children.size(); i++) {
        if (children[i] == child) {
            //delete child;
            children.erase(children.begin() + i);
        }
    }
}

void DisplayObjectContainer::removeImmediateChild(string id) {
    for (int i = 0; i < children.size(); i++) {
        if (children[i]->id == id) {
            // delete the child
            //delete children[i];
            children.erase(children.begin() + i);
        }
    }
}

void DisplayObjectContainer::removeChild(int index) {
    if (index < children.size()) {
        //delete children[index];
        children.erase(children.begin() + index);
    }
}

void DisplayObjectContainer::removeThis() {
    if (this->parent != NULL) {
        ((DisplayObjectContainer*)this->parent)->removeImmediateChild(this);
    }
}

int DisplayObjectContainer::numChildren() {
    return this->children.size();
}

DisplayObject* DisplayObjectContainer::getChild(int index) {
    if (index < 0 || index > numChildren()) {
        return NULL;
    }
    else return children[index];
}

DisplayObject* DisplayObjectContainer::getChild(string id) {
    for (int i = 0; i < children.size(); i++) {
        if (children[i]->id == id) {
            return children[i];
        }
        // check recursively?
    }
    return NULL;
}

void DisplayObjectContainer::update(set<SDL_Scancode> pressedKeys, ControllerInput controllerInput) {
    DisplayObject::update(pressedKeys, controllerInput);
    for (int i = 0; i < children.size(); i++) {
        children[i]->update(pressedKeys, controllerInput);
    }
}


void DisplayObjectContainer::draw(AffineTransform &at) {
    DisplayObject::draw(at);

    applyTransformations(at);
    // undo the parent's pivot
    at.translate(pivot.x, pivot.y);
    for (int i = 0; i < children.size(); i++) {
        if (camPerspective)
        {
            children[i]->setScrollSpeed(scrollSpeed);
        }
        children[i]->draw(at);
    }
    // redo the parent's pivot
    at.translate(-pivot.x, -pivot.y);
    reverseTransformations(at);
}
