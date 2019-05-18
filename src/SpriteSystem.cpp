#include "SpriteSystem.h"

//-----------------------------------------------------------
// Sprite System is the collection of all sprites
// in this case, they are mostly rockets
//

//  Add a Sprite to the Sprite System
//
void SpriteSystem::add(Sprite s) {
    sprites.push_back(s);
}

// Remove a sprite from the sprite system. Note that this function is not currently
// used. The typical case is that sprites automatically get removed when the reach
// their lifespan.
//
void SpriteSystem::remove(int i) {
    sprites.erase(sprites.begin() + i);
}

// remove all sprites within a given dist of point
//
bool SpriteSystem::removeNear(ofVec3f point, float dist) {
    vector<Sprite>::iterator s = sprites.begin();
    vector<Sprite>::iterator tmp;
    bool res;
    
    while (s != sprites.end()) {
        ofVec3f v = s->trans - point;
        if (v.length() < dist) {
            tmp = sprites.erase(s);
            s = tmp;
            //res = true;
            return true;
        }
        else{
            s++;
            //res = false;
            //return false;
        }
    }
    return false;
}

void SpriteSystem::removeAll() {
    for(int i = 0; i < sprites.size(); i++)
        sprites[i].lifespan = 0;
}

//  Update the SpriteSystem by checking which sprites have exceeded their
//  lifespan (and deleting).  Also the sprite is moved to it's next
//  location based on velocity and direction.
//
void SpriteSystem::update() {
    
    if (sprites.size() == 0) return;
    vector<Sprite>::iterator s = sprites.begin();
    vector<Sprite>::iterator tmp;
    
    // check which sprites have exceed their lifespan and delete
    // from list.  When deleting multiple objects from a vector while
    // traversing at the same time, use an iterator.
    //
    while (s != sprites.end()) {
        if (s->lifespan != -1 && s->age() > s->lifespan) {
            //            cout << "deleting sprite: " << s->name << endl;
            tmp = sprites.erase(s);
            s = tmp;
        }
        else s++;
    }
    
    //  Move sprite
    //
    for (int i = 0; i < sprites.size(); i++) {
        sprites[i].trans += sprites[i].velocity / ofGetFrameRate();
    }
}

//  Render all the sprites
//
void SpriteSystem::draw() {
    for (int i = 0; i < sprites.size(); i++) {
        sprites[i].draw();
    }
}

int SpriteSystem::size(){
    return sprites.size();
}
