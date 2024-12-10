#pragma once

#include <vector>
#include "CorpsRigide.h"
#include "PhysicsIntegrator.h"
#include "octree.h"
#include "Collision.h"


class World {
public:
    World();

    // Add a particle to the world
    void addCorpsRigide(CorpsRigide* corps);

    // Update the world (apply forces, update particle positions, handle collisions)
    void update(float deltaTime);

    void draw();

    void updateOctree();

    //std::vector<Particle*>& getParticles();

private:
    vector<CorpsRigide*> sceneObject;
    PhysicsIntegrator physicsIntegrator;
    OctreeNode* octree;
};
