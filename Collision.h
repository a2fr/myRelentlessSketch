#pragma once
#include "CorpsRigide.h"
#include "BoundingSphere.h"
#include <vector>
#include "Octree.h"

class Collision {
public:
    static void detectAndResolveCollisions(std::vector<CorpsRigide*>& corpsObjects, OctreeNode* octree);
private:
    static void applyCollisionForce(CorpsRigide* corps1, CorpsRigide* corps2);
    static bool isCollision(BoundingSphere* sphere1, BoundingSphere* sphere2);
    static void getNodesWithMultipleObjects(OctreeNode* node, std::vector<OctreeNode*>& nodesToCheck);
    static void detectCollisionWithGround(CorpsRigide* corps, float restitution);
};
