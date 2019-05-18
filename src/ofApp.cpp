#include "ofApp.h"
#include "Emitter.h"
//-----------------------------------------------
//
// Modified base on the source code
// from Professor Kevin M. Smith - CS 134 SJSU
//
//
//

//--------------------------------------------------------------
// set up emitters (spaceship), and also its child (rockets)
// load up necessary images and music for the UI
// simple BLACK background color for part 1
// positioning all elements for running the game
//
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofBackground(0, 0, 0);
    
    // Hero Spaceship setup
    //
    heroSpaceship = new Emitter();
    heroMissiles =  new SpriteSystem() ;
    heroSpaceship->setChildSize(10, 10);
    //collider.setPosition(ofVec3f(800, 800));
    //collider.width = 100;
    //collider.height = 100;
    heroSkinLoaded = false;
    
    // Invader spaceship setup
    //
    // Center
    invaderSpawnerC = new Emitter();
    invaderShipsC = new SpriteSystem();
    invaderSpawnerC->setChildSize(10, 10);
    
    // Left Side
    invaderSpawnerLS = new Emitter();
    invaderShipsLS = new SpriteSystem();
    invaderSpawnerLS->setChildSize(10, 10);
    
    // Right Side
    invaderSpawnerRS = new Emitter();
    invaderShipsRS = new SpriteSystem();
    invaderSpawnerRS->setChildSize(10, 10);
    
    
    /*if (defaultImage.loadImage("images/space-invaders-ship-scaled.png")) {
     emitter->setChildImage(defaultImage);
     imageLoaded = true;
     }*/
    
    gui.setup();
    gui.add(rate.setup("rate", 50, 1, 100));
    gui.add(velocity.setup("velocity", ofVec3f(0, -1000, 0), ofVec3f(-1000, -1000, -1000), ofVec3f(1000, 1000, 1000)));
    gui.add(radialForceVal.setup("Radial Force", 1000, 100, 5000));
    bHide = true;
    
    // Physics
    //
    radialForce = new ImpulseRadialForce(radialForceVal);
    explosionEmitter.sys->addForce(radialForce);
    explosionEmitter.setLifespan(0.5);
    explosionEmitter.setRate(1.0);
    explosionEmitter.setParticleRadius(5);
    explosionEmitter.setGroupSize(10);
    explosionEmitter.setOneShot(true);
    explosionEmitter.setEmitterType(RadialEmitter);
    
    // loading image for the spaceship
    //
    if (heroSkin.load("images/Falcon.png")) {
        heroSkinLoaded = true;
        heroSpaceship->haveImage = true;
    }
    else {
        ofLogFatalError("can't load image: images/space-invaders-ship-scaled.png");
        ofExit();
    }
    
    // loading image for the rockets
    //
    if (heroMissileSkin.load("images/missile.png")) {
        heroMissileSkinLoaded = true;
        heroSpaceship->haveChildImage = true;
    }
    else {
        ofLogFatalError("can't load image: images/space-invaders-ship-scaled.png");
        ofExit();
    }
    
    // loading the rocket firing sound
    //
    if(missileSoundPlay.load("sounds/missile-fire.mp3")) missileSoundLoaded = true;
    
    // set the initial position of the spaceship in the middle of the screen
    //
    heroSpaceship->setPosition(ofVec3f(ofGetWindowWidth()/2, ofGetWindowHeight()-100, 0));
    heroSpaceship->start();
    
    // set the initial position of the invader in the top of the screen
    // set drawable to false to prevent from drawing
    //
    invaderSpawnerC->setPosition(ofVec3f(ofGetWindowWidth()/2, 0, 0));
    invaderSpawnerC->drawable = false;
    invaderSpawnerC->start();
    
    invaderSpawnerRS->setPosition(ofVec3f(ofGetWindowWidth(), 0, 0));
    invaderSpawnerRS->drawable = false;
    invaderSpawnerRS->start();
    
    invaderSpawnerLS->setPosition(ofVec3f(0, 0, 0));
    invaderSpawnerLS->drawable = false;
    invaderSpawnerLS->start();
    
    // loading image for the center invaderships
    //
    if (invaderSkinC.load("images/invader-2.png")) {
        invaderSkinLoadedC = true;
        invaderSpawnerC->haveChildImage = true;
    }
    else {
        ofLogFatalError("can't load image: images/invader-2.png");
        ofExit();
    }
    // loading image for the side invaderships
    //
    if (invaderSkinS.load("images/invader-1.png")) {
        invaderSkinLoadedS = true;
        invaderSpawnerRS->haveChildImage = true;
        invaderSpawnerLS->haveChildImage = true;
    }
    else {
        ofLogFatalError("can't load image: images/invader-1.png");
        ofExit();
    }
    // loading the rocket firing sound
    //
    if(explosionSoundPlay.load("sounds/explosion.mp3")) explosionSoundLoaded = true;
    if(backgroundSoundPlay.load("sounds/Star Wars.mp3")){
        backgroundSoundloaded = true;
        backgroundSoundPlay.setLoop(true);
    }
}

//--------------------------------------------------------------
// using startGame to check if SPACEBAR is pressed for the 1st time
// otherwise game will remine IDLE (cannot fire rockets)
//
// then using fireMissile to check if SPACEBAR is pressed again to
// shoot missisles, when firing a missile, sets RATE, LIFESPAN, VELOCITY
// for the rocket
//
void ofApp::update() {
    if(backgroundSoundloaded && forOnce){
        cout << "Playing... " << endl;
        backgroundSoundPlay.play();
        forOnce = false;
    }
    
    if(heroSpaceship->lifespan == 0){
        //startGame = false;
        startEnemyC = false;
        startEnemyS = false;
        
        invaderShipsC->removeAll();
        invaderShipsLS->removeAll();
        invaderShipsRS->removeAll();

        startGame = false;;
    }
    else{
        if(startGame){
            
            // Hero Spaceship Section
            // Missile firing machanism
            //
            if(fireMissile){
                Sprite tempSpr;
                heroSpaceship->setRate(rate);
                heroSpaceship->setVelocity((ofVec3f) velocity);
                
                // Added function in Emitter, spriteGenerator()
                // it takes all the initial condition of the rocket
                // and create a rocket and push onto the SpriteSystem
                // which is the collection of all the rockets
                //
                tempSpr = heroSpaceship->spriteGenerator();
                heroMissiles -> add(tempSpr);
                
                // play rocket firing sound effect
                // only if the sound is loaded correctly
                //
                if(missileSoundLoaded) missileSoundPlay.play();
                
                // turn off the fire
                //
                fireMissile = false;
            }
            
            // Invadership Section
            //
            // Center Enemy
            if(startEnemyC){
                Sprite invaderShip;
                invaderSpawnerC->setRate(0.5);
                invaderSpawnerC->setLifespan(30000 * 1000);    // convert to milliseconds
                invaderSpawnerC->setVelocity(ofVec3f(0,90,0));
                
                invaderShip = invaderSpawnerC->spriteGenerator();
                invaderShipsC -> add(invaderShip);
            }
            
            // Side Enemy
            if(startEnemyS){
                Sprite invaderShipLS;
                invaderSpawnerLS->setRate(0.5);
                invaderSpawnerLS->setLifespan(30000 * 1000);    // convert to milliseconds
                invaderSpawnerLS->setVelocity(ofVec3f(90,90,0));
                
                invaderShipLS = invaderSpawnerLS->spriteGenerator();
                invaderShipsLS -> add(invaderShipLS);
                
                Sprite invaderShipRS;
                invaderSpawnerRS->setRate(0.5);
                invaderSpawnerRS->setLifespan(30000 * 1000);    // convert to milliseconds
                invaderSpawnerRS->setVelocity(ofVec3f(-90,90,0));
                
                invaderShipRS = invaderSpawnerRS->spriteGenerator();
                invaderShipsRS -> add(invaderShipRS);
                
            }
            
            // Physics
            //
            radialForce->setRadial(radialForceVal);
            
            // Collision Detection
            //
            checkCollisions();
            if(score >= 50 && score <120) {
                stage = 1;
                invaderSpawnerC->setVelocity(ofVec3f(0,150,0));
            }
            else if(score >= 120 && score <= 200)
            {
                stage = 2;
                startEnemyS = true;
            }
            else if(score >= 200) {
                stage = 3;
                invaderSpawnerRS->setVelocity(ofVec3f(-240,240,0));
                invaderSpawnerLS->setVelocity(ofVec3f(240,240,0));
            }
            // keep updateing the sprites that are already on
            // the UI, to keep rockets moving
            //
            heroSpaceship->update();
            explosionEmitter.update();
            heroMissiles -> update();
            invaderShipsC -> update();
            invaderShipsRS -> update();
            invaderShipsLS -> update();

        }
    }
}


//--------------------------------------------------------------
// draw the Emitter (spaceship), the rockets (spriteSystem)
// check if the MENU is open, if YES, display the menu
// call Emitters to draw spaceship and rockets
//
void ofApp::draw(){
    // heroSpaceship and missile Drawing section
    //
    heroSpaceship->draw();
    //collider.draw();
    heroMissiles->draw();
    
    // Hero Skin
    if(heroSkinLoaded) heroSpaceship->setImage(heroSkin);                // SPACESHIP
    if(heroMissileSkinLoaded) heroSpaceship->setChildImage(heroMissileSkin);  // ROCKETS
    
    // Invader Skin
    if(invaderSkinLoadedC) invaderSpawnerC->setChildImage(invaderSkinC);
    if(invaderSkinLoadedS) invaderSpawnerRS->setChildImage(invaderSkinS);
    if(invaderSkinLoadedS) invaderSpawnerLS->setChildImage(invaderSkinS);
    
    // invaderSpawner and incvaderShips Drawing section
    //
    invaderSpawnerC->draw();
    invaderShipsC->draw();
    
    invaderSpawnerLS->draw();
    invaderShipsLS->draw();
    
    invaderSpawnerRS->draw();
    invaderShipsRS->draw();
    
    explosionEmitter.draw();
    
    if (!bHide) {
        gui.draw();
    }
    
    if(!startGame){
        
        string gameOver;
        gameOver = "GAME OVER";
        string scoreTotal;
        scoreTotal = "Your earned: " + std::to_string(score) + " points!!!";
        ofDrawBitmapString(gameOver, ofGetWindowWidth()/2-40, ofGetWindowHeight()/2);
        ofDrawBitmapString(scoreTotal, ofGetWindowWidth()/2-80, ofGetWindowHeight()/2+15);
    }
    else{
        string str;
        str = "Your Score: " + std::to_string(score);
        ofDrawBitmapString(str, ofGetWindowWidth() -170, 15);
        string level;
        level = "Your Level " + std::to_string(stage);
        ofDrawBitmapString(level, ofGetWindowWidth()-170, 30);
        string life;
        life = "Your life: " + std::to_string(heroSpaceship->lifespan/1000);
        ofDrawBitmapString(life, ofGetWindowWidth()-170, 45);
    }

}

// Checking rocket collision by iterating the invaderships spritesystem
// if there is detection, invadership will reduce lifespan (in this case
// it will reduce all the lifespan)
// then play explosion sound
//
void ofApp::checkCollisions() {
    
    // center coming invaderships
    //
    for(int i = 0; i < invaderShipsC->size(); i++){
        if(invaderShipsC->removeNear(heroSpaceship->trans, heroSpaceship->width)){
            heroSpaceship->setLifespan( heroSpaceship->lifespan - 1000 );
        }
        if(heroMissiles->removeNear(invaderShipsC->sprites[i].trans, invaderShipsC->sprites[i].width)) {
            invaderShipsC->sprites[i].lifespan = invaderShipsC->sprites[i].lifespan - (30000*1000);
            if(invaderShipsC->sprites[i].lifespan == 0) {
                explosionSoundPlay.play();
                // score for gameplay
                score = score + 20;
                
                explosionEmitter.sys->reset();
                explosionEmitter.setPosition(invaderShipsC->sprites[i].trans);
                explosionEmitter.sys->setVelocity(invaderShipsC->sprites[i].trans);
                explosionEmitter.start();
            }
        }
    }
    
    // left side coming invaderships
    //
    for(int i = 0; i < invaderShipsLS->size(); i++){
        if(invaderShipsLS->removeNear(heroSpaceship->trans, heroSpaceship->width)){
            heroSpaceship->setLifespan( heroSpaceship->lifespan - 1000 );
        }
        if(heroMissiles->removeNear(invaderShipsLS->sprites[i].trans, invaderShipsLS->sprites[i].width)) {
            invaderShipsLS->sprites[i].lifespan = invaderShipsLS->sprites[i].lifespan - (30000*1000);
            if(invaderShipsLS->sprites[i].lifespan == 0) explosionSoundPlay.play();
            // score for gameplay
            score = score + 10;
            
            explosionEmitter.sys->reset();
            explosionEmitter.setPosition(invaderShipsLS->sprites[i].trans);
            explosionEmitter.sys->setVelocity(invaderShipsLS->sprites[i].trans);
            explosionEmitter.start();
        }
    }
    
    // right side coming invaderships
    //
    for(int i = 0; i < invaderShipsRS->size(); i++){
        if(invaderShipsRS->removeNear(heroSpaceship->trans, heroSpaceship->width)){
            heroSpaceship->setLifespan( heroSpaceship->lifespan - 1000 );
        }
        if(heroMissiles->removeNear(invaderShipsRS->sprites[i].trans, invaderShipsRS->sprites[i].width)) {
            invaderShipsRS->sprites[i].lifespan = invaderShipsRS->sprites[i].lifespan - (30000*1000);
            if(invaderShipsRS->sprites[i].lifespan == 0) explosionSoundPlay.play();
            // score for gameplay
            score = score + 10;
            
            explosionEmitter.sys->reset();
            explosionEmitter.setPosition(invaderShipsRS->sprites[i].trans);
            explosionEmitter.sys->setVelocity(invaderShipsRS->sprites[i].trans);
            explosionEmitter.start();
        }
    }
    
}


//--------------------------------------------------------------

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    //    cout << "mouse( " << x << "," << y << ")" << endl;
}

//--------------------------------------------------------------
// Using MoveLock to lock on movements in case the mouse move out of the
// area of the spaceship during a movement
// Then checking the spaceship boundaries according to the screen size
//
void ofApp::mouseDragged(int x, int y, int button){
    ofPoint mouse_cur = ofPoint(x, y);                      // mouse position
    hSpaceshipPosition = glm::vec3(heroSpaceship->x, heroSpaceship->y, 0);    // spaceship center
    if(moveLock){
        
        // Most Left
        if((hSpaceshipPosition.x+((heroSpaceship->width)/2)) >= 1334){
            ofVec3f delta = mouse_cur - mouse_last;
            if(delta.x > 0){
                heroSpaceship->trans.y += delta.y;
                mouse_last = mouse_cur;
            }
            else{
                heroSpaceship->trans += delta;
                mouse_last = mouse_cur;
            }
        }
        
        // Most Right
        else if((hSpaceshipPosition.x-((heroSpaceship->width)/2)) <= 0){
            ofVec3f delta = mouse_cur - mouse_last;
            if(delta.x < 0){
                heroSpaceship->trans.y += delta.y;
                mouse_last = mouse_cur;
            }
            else{
                heroSpaceship->trans += delta;
                mouse_last = mouse_cur;
            }
        }
        
        // Most Down
        else if((hSpaceshipPosition.y+((heroSpaceship->height)/2)) >= 750){
            ofVec3f delta = mouse_cur - mouse_last;
            if(delta.y > 0){
                heroSpaceship->trans.x += delta.x;
                mouse_last = mouse_cur;
            }
            else{
                heroSpaceship->trans += delta;
                mouse_last = mouse_cur;
            }
        }
        
        // Most Up
        else if((hSpaceshipPosition.y-((heroSpaceship->height)/2)) <= 0){
            ofVec3f delta = mouse_cur - mouse_last;
            if(delta.y < 0){
                heroSpaceship->trans.x += delta.x;
                mouse_last = mouse_cur;
            }
            else{
                heroSpaceship->trans += delta;
                mouse_last = mouse_cur;
            }
        }
        
        // Normal Movements
        //
        else{
            ofVec3f delta = mouse_cur - mouse_last;
            heroSpaceship->trans += delta;
            mouse_last = mouse_cur;
        }
    }
}

//--------------------------------------------------------------
// checking when mouse pressed is inside of the spaceship
//
void ofApp::mousePressed(int x, int y, int button){
    //cout << "x : " << x << " y: " << y << endl;
    p = glm::vec3(x,y,0);
    hSpaceshipPosition = glm::vec3(heroSpaceship->x, heroSpaceship->y, 0);
    if(insideShapeSqr(p, hSpaceshipPosition, heroSpaceship->width, heroSpaceship->height)){
        //cout << "HITTTTT" << endl;
        moveLock = true;
    }
    mouse_last = ofPoint(x, y);
}

//--------------------------------------------------------------
// turn moveLock off when mouse is released
//
void ofApp::mouseReleased(int x, int y, int button){
    if(moveLock) moveLock = false;
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

void ofApp::keyPressed(int key) {
    if (key == keyKey) {
        return;
    }
    switch (key) {
        case OF_KEY_UP:
            
            if(heroSpaceship->getPosition().y-heroSpaceship->height/2>=0)
                heroSpaceship->setHeroVelocity(ofVec3f(0,-250,0));
            else
                heroSpaceship->setHeroVelocity(ofVec3f(0,0,0));
            key = keyKey;
            break;
        case OF_KEY_DOWN:
           
            if(heroSpaceship->getPosition().y+heroSpaceship->height/2<=ofGetWindowHeight())
                 heroSpaceship->setHeroVelocity(ofVec3f(0,250,0));
            else
                heroSpaceship->setHeroVelocity(ofVec3f(0,0,0));
            key = keyKey;
            break;
        case OF_KEY_LEFT:
            if(heroSpaceship->getPosition().x-heroSpaceship->width/2>=0)
                 heroSpaceship->setHeroVelocity(ofVec3f(-250,0,0));
            else
                heroSpaceship->setHeroVelocity(ofVec3f(0,0,0));
            key = keyKey;
            break;
        case OF_KEY_RIGHT:
            if(heroSpaceship->getPosition().x+heroSpaceship->width/2<=ofGetWindowWidth())
                heroSpaceship->setHeroVelocity(ofVec3f(250,0,0));
            else
                heroSpaceship->setHeroVelocity(ofVec3f(0,0,0));
            key = keyKey;
            break;
        case 'F':
        case 'f':
            ofToggleFullscreen();
            break;
        case 'H':
        case 'h':
            bHide = !bHide;
            break;
        case 'r':
            break;
        case 'u':
            break;
        case OF_KEY_ALT:
            break;
        case OF_KEY_CONTROL:
            break;
        case OF_KEY_SHIFT:
            break;
        case OF_KEY_DEL:
            break;
        case 'c':
            startEnemyC = true;
            break;
        case 'C':
            startEnemyC = false;
            break;
        case 's':
            startEnemyS = true;
            break;
        case 'S':
            startEnemyS = false;
            break;
        case ' ':
            // use space key to start the game
            // break it from idle mode
            //
            if(!startGame) {
                startGame = true;
                startEnemyC = true; 
            }
            else{
                fireMissile = true;
            }
            break;
    }
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    switch (key) {
        case OF_KEY_LEFT:
            heroSpaceship->setHeroVelocity(ofVec3f(0,0,0));
            break;
        case OF_KEY_RIGHT:
            heroSpaceship->setHeroVelocity(ofVec3f(0,0,0));
            break;
        case OF_KEY_UP:
            heroSpaceship->setHeroVelocity(ofVec3f(0,0,0));
            break;
        case OF_KEY_DOWN:
            heroSpaceship->setHeroVelocity(ofVec3f(0,0,0));
            break;
        case OF_KEY_ALT:
            break;
        case OF_KEY_CONTROL:
            break;
        case OF_KEY_SHIFT:
            break;
        case ' ':
            break;
    }
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}

