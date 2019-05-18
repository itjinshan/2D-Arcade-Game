#pragma once
//-----------------------------------------------
//
// Modified base on the source code
// from ProfessorKevin M. Smith - CS 134 SJSU
//
//
//
#include "ofMain.h"
#include "ofxGui.h"
#include "Sprite.h"
#include "SpriteSystem.h"
#include "ParticleSystem.h"
#include "ParticleEmitter.h"


typedef enum { MoveStop, MoveLeft, MoveRight, MoveUp, MoveDown } MoveDir;



class Emitter;

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void checkCollisions();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    // Objects
    //
    
    // Spaceship
    //
    Emitter *heroSpaceship;               // spaceship
    Sprite collider;                  // collision test
    SpriteSystem *heroMissiles;      // collection of rockets
    
    // Enemies
    //
    // Center Enemy Spawner
    //
    Emitter *invaderSpawnerC;
    SpriteSystem *invaderShipsC;
    
    // Left Side Enemy Spawner
    //
    Emitter *invaderSpawnerLS;
    SpriteSystem *invaderShipsLS;
    
    // Left Side Enemy Spawner
    Emitter * invaderSpawnerRS;
    SpriteSystem *invaderShipsRS;
    
    // Explosion Emmitter
    ParticleEmitter  explosionEmitter;
    
    // player Score
    int score = 0;
    int stage = 0;
    
    // Hero Spaceship images and sound controls
    //
    ofSoundPlayer missileSoundPlay, explosionSoundPlay, backgroundSoundPlay;
    ofImage heroSkin, heroMissileSkin;
    ofImage invaderSkinC, invaderSkinS;
    ofVec3f mouse_last;
    bool heroSkinLoaded;
    bool heroMissileSkinLoaded;
    bool missileSoundLoaded;
    bool backgroundSoundloaded;
    bool explosionSoundLoaded;
    bool invaderSkinLoadedC;
    bool invaderSkinLoadedS;
    bool forOnce = true;
    
    // Physics Adding Forces
    //
    ImpulseRadialForce *radialForce;
    
    //  UI control
    //
    bool bHide;
    bool startGame = false;
    bool fireMissile = false;
    bool moveLock = false;
    bool startEnemyC = false;
    bool startEnemyS = false;
    
    int prevKey = -99999999999;
    
    // OF controls
    ofxFloatSlider rate;
    ofxVec3Slider velocity;
    ofxLabel screenSize;
    ofxFloatSlider radialForceVal;
    ofxPanel gui;
    
    // recording current position and
    // spaceship center position
    glm::vec3 p;
    glm::vec3 hSpaceshipPosition;
    
    // checking mouse pressed is inside of spaceship
    bool insideShapeSqr(glm::vec3 p, glm::vec3 boxp, float width, float height){
        //inside a box
        //p = position and o = original
        
        glm::vec3 o = glm::vec3(boxp.x - width / 2.0, boxp.y - height/2.0, 0);
        //boxp = box position
        
        return (p.x >= o.x && p.x < o.x + width && p.y >= o.y && p.y < o.y + height);
    }
};
