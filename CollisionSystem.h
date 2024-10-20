#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include "Particle.h"
#include "ParticleGravity.h"
#include <vector>

class CollisionSystem {
public:
    void detectAndResolveCollisions(std::vector<Particle*>& particles, float deltaTime, ParticleGravity* gravity, float dynamicFrictionCoeff, float normalForce);
    void enforceCableConstraint(Particle& p1, Particle& p2, float maxLength);
    void enforceSteelRodConstraint(Particle& p1, Particle& p2, float fixedLength);

private:
    bool checkForCollision(const Particle& p1, const Particle& p2);
    void resolveCollision(Particle& p1, Particle& p2);
    bool checkForStationaryCollision(const Particle& p, const Vector& gravity);
    void checkForGroundCollision(Particle& p, float groundY, float dynamicFrictionCoeff, float normalForce);
};

#endif // COLLISION_SYSTEM_H
