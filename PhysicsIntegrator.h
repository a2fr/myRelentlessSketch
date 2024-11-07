// PhysicsIntegrator.h
#ifndef PHYSICSINTEGRATOR_H
#define PHYSICSINTEGRATOR_H

#include "CorpsRigide.h"
#include "Vector.h"

class PhysicsIntegrator {
public:
    void update(CorpsRigide& corps, double duration);
    void addForce(CorpsRigide* corps, const Vector& force);
};

#endif // PHYSICSINTEGRATOR_H
