#pragma once
//-----------------------------------------------
//
// Modified base on the source code
// from ProfessorKevin M. Smith - CS 134 SJSU
//
//
//

#include "ofMain.h"

// This is a base object that all drawable object inherit from
// It is possible this will be replaced by ofNode when we move to 3D
//
class BaseObject {
public:
    BaseObject();
    ofVec2f trans, scale;
    float    rot;
    bool    bSelected;
    void setPosition(ofVec3f);
    ofVec3f getPosition();
};

//  General Sprite class  (similar to a Particle)
//
class Sprite : public BaseObject {
public:
    Sprite();
    void draw();
    float age();
    void setImage(ofImage);
    float speed;    //   in pixels/sec
    ofVec3f velocity; // in pixels/sec
    ofImage image;
    float birthtime; // elapsed time in ms
    float lifespan;  //  time in ms
    string name;
    bool haveImage;
    float width, height;
};

