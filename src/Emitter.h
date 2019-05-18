#pragma once
//-----------------------------------------------
//
// Modified base on the source code
// from ProfessorKevin M. Smith - CS 134 SJSU
//
//
//

#include "Sprite.h"
#include "SpriteSystem.h"


//  General purpose Emitter class for emitting sprites
//  This works similar to a Particle emitter
//
class Emitter : public BaseObject {
public:
    Emitter();
    void draw();
    void start();
    void stop();
    void setLifespan(int);
    void setVelocity(ofVec3f);
    void setHeroVelocity(ofVec3f);
    void setChildImage(ofImage);
    void setChildSize(float w, float h) { childWidth = w; childHeight = h; }
    void setImage(ofImage);
    void setRate(float);
    
    Sprite spriteGenerator ();
    
    float maxDistPerFrame();
    void update();
    float rate;
    ofVec3f velocity;
    ofVec3f heroVelocity;
    int lifespan;
    bool started;
    float lastSpawned;
    
    // Image and sound control
    //
    ofImage childImage;
    ofImage image;
    bool drawable;
    bool haveChildImage;
    bool haveImage;
    float width, height;
    float childWidth, childHeight;
    
    float x, y;

};
