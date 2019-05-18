#pragma once
#include "Sprite.h"
#include "ofMain.h"

//  Manages all Sprites in a system.  You can create multiple systems
//
class SpriteSystem : public BaseObject{
    public:
        void add(Sprite);
        void remove(int);
        void update();
        bool removeNear(ofVec3f point, float dist);
        void removeAll();
        void draw();
        int size();
        vector<Sprite> sprites;
};

    

