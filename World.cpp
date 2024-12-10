#include "World.h"


World::World() {
    physicsIntegrator = PhysicsIntegrator();
    BoundingBox box(Vector(-500, 0, -500), Vector(500, 500, 500));
    octree = new OctreeNode(box);
}

void World::addCorpsRigide(CorpsRigide* corps)
{
    sceneObject.push_back(corps);
    octree->Insert(&corps->boundingSphere);
}

void World::update(float deltaTime) {

     for (CorpsRigide* corps : sceneObject) {
       physicsIntegrator.update(*corps, ofGetLastFrameTime());
     }
     Collision::detectAndResolveCollisions(sceneObject, octree);
     updateOctree();
}

void World::draw()
{
    for (CorpsRigide* corps : sceneObject) {
        // Trace
        ofSetColor(0, 0, 200);
        for (auto const& point : corps->trace) {
            ofDrawSphere(point.getGlmVec(), 0.2);
        }
        corps->draw();
    }

    octree->draw();
}

void World::updateOctree()
{
    delete octree;
    BoundingBox box(Vector(-500, 0, -500), Vector(500, 500, 500));
    octree = new OctreeNode(box);

    for(auto* corps : sceneObject){
        octree->Insert(&corps->boundingSphere);
    }
}


