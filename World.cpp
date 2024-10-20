#include "World.h"

World::World() {
    // Initialize the gravity force generator
    gravity = new ParticleGravity(Vector(0, 9.81, 0));
    friction = new ParticleFriction(staticFrictionCoeff, dynamicFrictionCoeff, normalForce);
}

void World::addBlob(MyBlob* blob) {
    blobs.push_back(blob);
}

void World::update(float deltaTime) {
    
    for (MyBlob* b : blobs) {
        for (Particle* p : b->particles) {
            forceRegistry.add(p, gravity);
            forceRegistry.add(p, friction);
        }

        ParticleSpring* spring;
        ParticleSpring* springInverse;
        for (int i = 1; i < b->particles.size() - 1; ++i) {
            spring = new ParticleSpring(b->particles[i], springConstant, restLength);
            forceRegistry.add(b->particles[0], spring);
            springInverse = new ParticleSpring(b->particles[0], springConstant, restLength);
            forceRegistry.add(b->particles[i], springInverse);

            spring = new ParticleSpring(b->particles[i], springConstant, restLength);
            forceRegistry.add(b->particles[i+1], spring);
            springInverse = new ParticleSpring(b->particles[i+1], springConstant, restLength);
            forceRegistry.add(b->particles[i], springInverse);
        }

        int last = b->particles.size() - 1;
        spring = new ParticleSpring(b->particles[last], springConstant, restLength);
        forceRegistry.add(b->particles[0], spring);
        springInverse = new ParticleSpring(b->particles[0], springConstant, restLength);
        forceRegistry.add(b->particles[last], springInverse);

        spring = new ParticleSpring(b->particles[last], springConstant, restLength);
        forceRegistry.add(b->particles[1], spring);
        springInverse = new ParticleSpring(b->particles[1], springConstant, restLength);
        forceRegistry.add(b->particles[last], springInverse);
    }

    // Apply forces to all particles
    forceRegistry.updateForces(deltaTime);
    forceRegistry.clear();
    for (MyBlob* b : blobs){
        // Check for collisions and resolve them
        collisionSystem.detectAndResolveCollisions(b->particles, deltaTime, gravity, dynamicFrictionCoeff, normalForce);
        // Update each particle's position based on forces applied
        for (Particle* p : b->particles) {
            p->update(deltaTime);
            p->clearAccum();
        }
    }
    
   
}

void World::draw()
{
    for (MyBlob* b : blobs) {
        b->draw();
    }
}


