#pragma once
#include "ParticleForceGenerator.h"
#include "Vector.h"

class ParticleFriction : public ParticleForceGenerator {
private:
    float staticFrictionCoefficient;  // Coefficient of static friction
    float dynamicFrictionCoefficient; // Coefficient of dynamic friction
    float normalForce;  // The normal force acting on the particle (usually gravity)

public:
    ParticleFriction(float staticCoeff, float dynamicCoeff, float normalForce);

    virtual void updateForce(Particle* particle, float duration) override;
};
