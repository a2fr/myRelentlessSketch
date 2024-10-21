#pragma once
#include "ParticleForceGenerator.h"
#include "Vector.h"

class ParticleFriction : public ParticleForceGenerator {
private:
    float staticFrictionCoefficient; 

    float k1, k2;

    float normalForce;  // The normal force acting on the particle (usually gravity)

public:
    ParticleFriction(float staticCoeff, float k1,float k2, float normalForce);

    virtual void updateForce(Particle* particle, float duration) override;
};
