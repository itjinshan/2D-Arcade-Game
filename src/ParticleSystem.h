#pragma once
//  Kevin M. Smith - CS 134 SJSU

#include "ofMain.h"
#include "Particle.h"


//  Pure Virtual Function Class - must be subclassed to create new forces.
//
class ParticleForce {
protected:
public:
	bool applyOnce = false;
	bool applied = false;
	virtual void updateForce(Particle *) = 0;
};

class ParticleSystem {
public:
	void add(const Particle &);
	void addForce(ParticleForce *);
	void remove(int);
	void update();
	void setLifespan(float);
    void setVelocity(ofVec3f);
    void setPosition(ofVec3f);
	void reset();
	int removeNear(const ofVec3f & point, float dist);
	void draw();
	vector<Particle> particles;
	vector<ParticleForce *> forces;
};



// Some convenient built-in forces
//
class GravityForce: public ParticleForce {
	ofVec3f gravity;
public:
	GravityForce(const ofVec3f & gravity);
    void setGravity(const float g) { gravity = ofVec3f(0,-g,0); }
	void updateForce(Particle *);
};

class TurbulenceForce : public ParticleForce {
	ofVec3f tmin, tmax;
public:
	TurbulenceForce(const ofVec3f & min, const ofVec3f &max);
    void setTubulence(const ofVec3f & min, const ofVec3f & max){ tmin = min; tmax = max;}
	void updateForce(Particle *);
};

class ImpulseRadialForce : public ParticleForce {
	float magnitude;
    float minY, maxY;
public:
	ImpulseRadialForce(float magnitude);
    ImpulseRadialForce(float magnitude, float yMin, float yMax);
    void setRadial(float r) { magnitude = r; }
	void updateForce(Particle *);
};
