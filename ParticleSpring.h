#pragma once
#include "ParticleForceGenerator.h"

class ParticleSpring : public ParticleForceGenerator {
private:
    Particle* other;
    float springConstant;
    float restLength;

public:
    ParticleSpring(Particle* other, float springConstant, float restLength);
    virtual void updateForce(Particle* particle, float duration) override;
};