#include "World.h"

World::World() {
    // Initialize the gravity force generator
    gravity = new ParticleGravity(); // Gravity pointing downward
}

void World::addParticle(Particle* particle) {
    particles.push_back(particle);
    forceRegistry.add(particle, gravity); // Add gravity to the particle
}

void World::update(float deltaTime) {
    // Apply forces to all particles
    forceRegistry.updateForces(deltaTime);

    // Update each particle's position based on forces applied
    for (Particle* p : particles) {
        p->update(deltaTime);
        p->clearAccum(); // Clear accumulated forces after each update
    }
}

std::vector<Particle*>& World::getParticles() {
    return particles;
}
