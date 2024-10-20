#pragma once

#include <vector>
#include "Particle.h"
#include "ParticleForceRegistry.h"
#include "ParticleGravity.h"

class World {
public:
    World();

    // Add a particle to the world
    void addParticle(Particle* particle);

    // Update the world (apply forces, update particle positions, handle collisions)
    void update(float deltaTime);

    // Get a list of active particles
    std::vector<Particle*>& getParticles();

private:
    std::vector<Particle*> particles;    // List of active particles
    ParticleForceRegistry forceRegistry; // Registry for managing forces
    ParticleGravity* gravity;            // Gravity force generator
};
