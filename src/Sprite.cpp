#include "Sprite.h"
//-----------------------------------------------
//
// Modified base on the source code
// from ProfessorKevin M. Smith - CS 134 SJSU
//
//
//
BaseObject::BaseObject() {
    trans = ofVec3f(0,0,0);
    scale = ofVec3f(1, 1, 1);
    rot = 0;
}

void BaseObject::setPosition(ofVec3f pos) {
    trans = pos;
}
    
ofVec3f BaseObject::getPosition() {
    return trans;
}

//
// Basic Sprite Object
//
Sprite::Sprite() {
    speed = 0;
    velocity = ofVec3f(0, 0, 0);
    lifespan = -1;      // lifespan of -1 => immortal
    birthtime = 0;
    bSelected = false;
    haveImage = false;
    name = "UnamedSprite";
    width = 20;
    height = 20;
}

// Return a sprite's age in milliseconds
//
float Sprite::age() {
    return (ofGetElapsedTimeMillis() - birthtime);
}

//  Set an image for the sprite. If you don't set one, a rectangle
//  gets drawn.
//
void Sprite::setImage(ofImage img) {
    image = img;
    haveImage = true;
    width = image.getWidth();
    height = image.getHeight();
}


//  Render the sprite
//
void Sprite::draw() {
    
    //ofSetColor(255, 255, 255, 255);
    
    // draw image centered and add in translation amount
    //
    if (haveImage) {
        image.draw(-width / 2.0 + trans.x, -height / 2.0 + trans.y);
    }
    else {
        // in case no image is supplied, draw something.
        //
        ofNoFill();
        //ofSetColor(255, 0, 0);
        ofDrawRectangle(-width / 2.0 + trans.x, -height / 2.0 + trans.y, width, height);
    }
}


