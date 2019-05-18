#include "ofMain.h"
#include "Emitter.h"
#include "SpriteSystem.h"

//-----------------------------------------------
//
// Modified base on the source code
// from ProfessorKevin M. Smith - CS 134 SJSU
//
//
//

//  Create a new Emitter - needs a SpriteSystem
//
Emitter::Emitter() {
    lifespan = 3000;    // milliseconds
    started = false;
    lastSpawned = 0;
    rate = 1;    // sprites/sec
    haveChildImage = false;
    haveImage = false;
    velocity = ofVec3f(100, 100, 0);
    heroVelocity = ofVec3f(0,0,0);
    drawable = true;
    width = 90;
    height = 90;
    childWidth = 10;
    childHeight = 10;
}

//  Draw the Emitter if it is drawable. In many cases you would want a hidden emitter
//
//
void Emitter::draw() {
    if (drawable) {
        
        // Load image and save it's x and y coordinates
        //
        if (haveImage) {
            x = trans.x;
            y = trans.y;
            image.draw(-image.getWidth() / 2.0 + trans.x, -image.getHeight() / 2.0 + trans.y);
        }
        else {
            //ofSetColor(0, 0, 255);
            x = trans.x;
            y = trans.y;
            ofDrawRectangle(-width / 2 + trans.x, -height / 2 + trans.y, width, height);
        }
    }
    
}

//  Update the Emitter. If it has been started, spawn new sprites with
//  initial velocity, lifespan, birthtime.
//
void Emitter::update() {
    // check for 0 framerate to avoid divide errors
    //
    float framerate = ofGetFrameRate();
    if (framerate < 1.0) return;
    
    // interval for this step
    //
    float dt = 1.0 / framerate;
    // update position based on velocity
    //
    trans += (heroVelocity * dt);
    
}

// Added function in Emitter, spriteGenerator()
// it takes all the initial condition of the rocket
// and create a rocket and push onto the SpriteSystem
// which is the collection of all the rockets
//
Sprite Emitter::spriteGenerator (){
    if (!started) return;
    
    Sprite sprite;
    float time = ofGetElapsedTimeMillis();
    if ((time - lastSpawned) > (1000.0 / rate)) {
    
        if (haveChildImage) sprite.setImage(childImage);
        sprite.velocity = velocity;
        sprite.lifespan = lifespan;
        sprite.setPosition(trans);
        sprite.birthtime = time;
        sprite.width = childWidth;
        sprite.height = childHeight;
        lastSpawned = time;
    }
    return sprite;
}


// Start/Stop the emitter.
//
void Emitter::start() {
    started = true;
    lastSpawned = ofGetElapsedTimeMillis();
}

void Emitter::stop() {
    started = false;
}


void Emitter::setLifespan(int life) {
    lifespan = life;
}

void Emitter::setVelocity(ofVec3f v) {
    velocity = v;
}

void Emitter::setHeroVelocity(ofVec3f v) {
    heroVelocity = v;
}

// set rocket images
//
void Emitter::setChildImage(ofImage img) {
    childImage = img;
    haveChildImage = true;
    childWidth = img.getWidth();
    childHeight = img.getHeight();
}

// set spaceship images
//
void Emitter::setImage(ofImage img) {
    image = img;
    width = img.getWidth();
    height = img.getHeight();
}

void Emitter::setRate(float r) {
    rate = r;
}

float Emitter::maxDistPerFrame() {
    return  velocity.length() / ofGetFrameRate();
}
