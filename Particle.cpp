#include "Particle.h"

Particle::Particle()
    : position(0, 0, 0), velocity(0, 0, 0), acceleration(0, 0, 0), inverseMass(0), radius(0), restitution(0) {}

Particle::Particle(ofVec3f pos, float mass, float radius)
    : position(pos), velocity(0, 0, 0), acceleration(0, 0, 0), inverseMass(mass > 0 ? 1.0f / mass : 0), radius(radius), restitution(0) {}

void Particle::addForce(const ofVec3f& force) {
    if (inverseMass > 0) {
        acceleration += force * inverseMass;
    }
}

void Particle::update(float deltaTime) {
    velocity += acceleration * deltaTime;
    position += velocity * deltaTime;
    acceleration.set(0, 0, 0); // Reset acceleration after each update
}

void Particle::draw() {
    ofDrawSphere(position, radius);
}

// Get mass function
float Particle::getMass() const {
	return inverseMass > 0 ? 1.0f / inverseMass : 0;
}