#pragma once

#include <vector>
#include "Particle.h"
#include "ParticleForceRegistry.h"
#include "ParticleGravity.h"
#include "ParticleFriction.h"
#include "ParticleSpring.h"
#include "CollisionSystem.h"
#include "MyBlob.h"

class World {
public:
    World();

    // Add a particle to the world
    void addBlob(MyBlob* blob);

    // Update the world (apply forces, update particle positions, handle collisions)
    void update(float deltaTime);

    void draw();

    //std::vector<Particle*>& getParticles();

private:
    std::vector<MyBlob*> blobs;
    ParticleForceRegistry forceRegistry; // Force registry to apply forces to particles
    
    //Gravity
    ParticleGravity* gravity;

    //Spring force
    float springConstant = 0.6f;
    float restLength = 100.0f; 

    // Initialize friction force generator
    ParticleFriction* friction;
    float staticFrictionCoeff = 0.1f; 
    float dynamicFrictionCoeff = 0.001f;
    float normalForce = 9.81f;
    float k1 = 0.4f;
    float k2 = 0.2f;

    //Collision systeme
    CollisionSystem collisionSystem;
};
