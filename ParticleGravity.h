#pragma once
#include "ForceGenerator.h"
#include "Particle.h"

class ParticleGravity : public ForceGenerator {
public:
    // Constructor to initialize gravity vector
    ParticleGravity(const ofVec3f& gravity) : gravity(gravity) {}

    // Apply the gravitational force to the particle
    virtual void applyForce(Particle* particle, float duration) {
        // If the particle has infinite mass (zero mass), do not apply force
        if (particle->getMass() <= 0.0f) {
            return;
        }

        // F = m * g (force = mass * gravity)
        ofVec3f force = gravity * particle->getMass();

        // Apply the force to the particle
        particle->addForce(force);
    }

private:
    ofVec3f gravity;  // Gravitational acceleration vector (e.g., (0, -9.81, 0))
};
