#include "AnimatedSprite.h"
#include "DisplayObject.h"
#include "Game.h"
#include <string>
#include <iostream> 
#include <rapidxml_utils.hpp>

using namespace std;
using namespace rapidxml;

AnimatedSprite::AnimatedSprite() : Sprite() {
    this->type = "AnimatedSprite";
}

AnimatedSprite::AnimatedSprite(string id) : Sprite(id, 0, 0, 0) {
    this->type = "AnimatedSprite";
    this->id = id;
}

AnimatedSprite::AnimatedSprite(string id, string spriteSheetPath, string xmlPath) : Sprite() {
    this->type = "AnimatedSprite";
    this->id = id;
    this->imgPath = spriteSheetPath;
    this->isSheet = true;
    addSSAnimation(spriteSheetPath, xmlPath);
}

AnimatedSprite::~AnimatedSprite() {
    for (Animation* an : animations) {
        for (int i = 0; i < an->numFrames; i++) {// this needs to be an iterator loop
            if(an->frames[i]->image != NULL) SDL_FreeSurface(an->frames[i]->image);
	        if(an->frames[i]->texture != NULL) SDL_DestroyTexture(an->frames[i]->texture);
            delete an->frames[i];
        }
        delete an->frames;
        delete an;
    }
}

void AnimatedSprite::addAnimation(string basepath, string animName, int numFrames, int frameRate, bool loop) {
    Animation* anim = new Animation();
    anim->animName = animName;
    anim->numFrames = numFrames;
    anim->frameRate = frameRate;
    anim->loop = loop;
    anim->curFrame = 0;
    anim->filepath = basepath;
    anim->frames = new Frame*[numFrames]; // new frame pointer array of size numFrames;
    for (int i = 0; i < numFrames; i++ ) {
        Frame* f = new Frame();
        string path = basepath + animName + "_" + to_string(i+1) + ".png";
        f->image = IMG_Load(path.c_str());
        f->texture = SDL_CreateTextureFromSurface(Game::renderer, f->image);
        anim->frames[i] = f;
    }
    animationNames.push_back(animName);
    animations.push_back(anim);
}

void AnimatedSprite::addSSAnimation(string filepath, string xmlPath){
    // Animation* anim = new Animation();
    this->isSheet = true;
    loadTexture(filepath);

    char path[xmlPath.length()+1]; 
    strcpy(path, xmlPath.c_str());
    
    // XML File Handler
    xml_document<> doc;
    file<> xmlFile(path);
    doc.parse<0>(xmlFile.data());
    xml_node<>* parent = doc.first_node("TextureAtlas");
    xml_node<>* child = parent->first_node();
    
    string prevAnim = process(child->first_attribute()->value());
    animationNames.push_back(prevAnim);
    int frameCount = 0;
    SSAnimation *temp = new SSAnimation;
    
    // For each sprite
    while(child) {
        // push sprite into existing animation
        if(!animationNames.empty() && animationNames.back() == prevAnim) {
            int x = stoi(child->first_attribute()->next_attribute("x")->value());
            int y = stoi(child->first_attribute()->next_attribute("y")->value());
            int w = stoi(child->first_attribute()->next_attribute("w")->value());
            int h = stoi(child->first_attribute()->next_attribute("h")->value());
            SDL_Rect frame = {x, y, w, h};
            temp->frames.push_back(frame);
            frameCount++;
        }
        else {
            // Add last animation
            temp->animName = prevAnim;
            temp->filepath = filepath;
            temp->numFrames = frameCount + 1;
            temp->frameRate = 2;
            temp->loop = true;
            temp->curFrame = 0;
            ssanimations.push_back(temp);
            animationNames.push_back(prevAnim);

            if(!child->next_sibling()) break;
            
            // Create new animation
            temp = new SSAnimation;
            frameCount = 0;
            prevAnim = process(child->first_attribute()->value());
            int x = stoi(child->first_attribute()->next_attribute("x")->value());
            int y = stoi(child->first_attribute()->next_attribute("y")->value());
            int w = stoi(child->first_attribute()->next_attribute("w")->value());
            int h = stoi(child->first_attribute()->next_attribute("h")->value());
            SDL_Rect frame = {x, y, w, h};
            temp->frames.push_back(frame);
        }
        child = child->next_sibling();
        if(child) {
            prevAnim = process(child->first_attribute()->value());
        }
        else {
            // Add last animation
            temp->animName = prevAnim;
            temp->filepath = filepath;
            temp->numFrames = frameCount;
            temp->frameRate = 2;
            temp->loop = true;
            temp->curFrame = 0;
            ssanimations.push_back(temp);
            animationNames.push_back(prevAnim);
        }
    }
}

Animation* AnimatedSprite::getAnimation(string animName) {
    for (int i = 0; i < animations.size(); i++) {
        if (animations[i]->animName == animName) {
            return animations[i];
        }
    }
    return NULL;
}

SSAnimation* AnimatedSprite::getSSAnimation(string animName) {
    for (int i = 0; i < ssanimations.size(); i++) {
        if (ssanimations[i]->animName == animName) {
            return ssanimations[i];
        }    
    }
    return NULL;
}

void AnimatedSprite::play(string animName) {
    Animation* anim;
    SSAnimation* ssanim;
    if(isSheet) {
        ssanim = getSSAnimation(animName);
        if (ssanim != NULL) {
            this->sscurrent = ssanim;
            this->sscurrent->curFrame = 0;
            frameCount = 0;
            playing = true;
        }
    }
    else {
        anim = getAnimation(animName);
        if (anim != NULL) {
            this->current = anim;
            this->current->curFrame = 0;
            frameCount = 0;
            playing = true;
        }
    }
}

void AnimatedSprite::replay() {
    if (this->current != NULL) {
        current->curFrame = 0;
        frameCount = 0;
        playing = true;
    }
    else if (this->sscurrent != NULL) {
        sscurrent->curFrame = 0;
        frameCount = 0;
        playing = true;
    }
}

void AnimatedSprite::stop() {
    this->playing = false;
}

void AnimatedSprite::update(set<SDL_Scancode> pressedKeys, ControllerInput controllerInput) {
    Sprite::update(pressedKeys, controllerInput);
    if (playing) {
        frameCount++;
        if (isSheet) {
            if (frameCount % sscurrent->frameRate == 0) {
                sscurrent->curFrame++;
                if (sscurrent->curFrame == sscurrent->numFrames) {
                    sscurrent->curFrame = 0;
                    if (!sscurrent->loop) stop();
                }
                srcrect = sscurrent->frames[sscurrent->curFrame];
            }
        }
        else if (!isSheet) {
            if (frameCount % current->frameRate == 0) {
                // increment local frame counter
                current->curFrame++;
                // check for array out of bounds
                if (current->curFrame == current->numFrames) {
                    // reset the animation
                    current->curFrame = 0;
                    // check for looping
                    if (!current->loop) {
                        stop();
                    }
                }
                DisplayObject::setTexture(current->frames[current->curFrame]->texture);
            }
        }

    }
    
}

void AnimatedSprite::draw(AffineTransform &at) {
    Sprite::draw(at);
}

string AnimatedSprite::process(string file) {
    string::size_type pos = file.find('_');
    return file.substr(0, pos);
}
