#include "World.h"

World::World() {
    // Initialize the gravity force generator
    gravity = new ParticleGravity(Vector(0, 9.81, 0));
    friction = new ParticleFriction(staticFrictionCoeff, k1, k2, normalForce);
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
        for (int i = 0; i < b->particles.size() - 2; ++i) {
            spring = new ParticleSpring(b->particles[i], springConstant, restLength);
            forceRegistry.add(b->particles[i+1], spring);
            springInverse = new ParticleSpring(b->particles[i+1], springConstant, restLength);
            forceRegistry.add(b->particles[i], springInverse);

            spring = new ParticleSpring(b->particles[i+2], springConstant, restLength);
            forceRegistry.add(b->particles[i], spring);
            springInverse = new ParticleSpring(b->particles[i], springConstant, restLength);
            forceRegistry.add(b->particles[i+2], springInverse);
        }

        int beforelast = b->particles.size() - 2;
        int last = b->particles.size() - 1;
        spring = new ParticleSpring(b->particles[beforelast], springConstant, restLength);
        forceRegistry.add(b->particles[last], spring);
        springInverse = new ParticleSpring(b->particles[last], springConstant, restLength);
        forceRegistry.add(b->particles[beforelast], springInverse);

        spring = new ParticleSpring(b->particles[beforelast], springConstant, restLength);
        forceRegistry.add(b->particles[0], spring);
        springInverse = new ParticleSpring(b->particles[0], springConstant, restLength);
        forceRegistry.add(b->particles[beforelast], springInverse);



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

    std::vector<Particle*> allParticles;
    for (MyBlob* b : blobs) {
        // Ajouter les particules de chaque blob à la liste
        allParticles.insert(allParticles.end(), b->particles.begin(), b->particles.end());
    }

    // Check for collisions and resolve them on all particles
    collisionSystem.detectAndResolveCollisions(allParticles, deltaTime, gravity, dynamicFrictionCoeff, normalForce, k1, k2, staticFrictionCoeff);

    for (MyBlob* b : blobs){
        // Update each particle's position based on forces applied
        for (Particle* p : b->particles) {
            p->update(deltaTime);
            p->clearAccum();
            p->handleInput();
        }
    }
}

void World::draw()
{
    for (MyBlob* b : blobs) {
        b->draw();
    }
}


