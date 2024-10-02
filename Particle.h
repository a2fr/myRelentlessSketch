#pragma once
#include "ofMain.h"

class Particle {
public:
    ofVec3f position;
    ofVec3f velocity;
    ofVec3f acceleration;
    float inverseMass; // Inverse of the mass (1/mass)
    float radius;
    float restitution; // Coefficient de restitution (pour les collisions)

    Particle();
    Particle(ofVec3f pos, float mass, float radius);

    void addForce(const ofVec3f& force);
    void update(float deltaTime);
    void draw();

	float getMass() const;
};
