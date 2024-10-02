#ifndef PARTICLE_FORCE_GENERATOR_H
#define PARTICLE_FORCE_GENERATOR_H

#include "Particle.h"

class ParticleForceGenerator {
public:
    virtual void updateForce(Particle* particle, float duration) = 0;
};


#endif // FORCE_GENERATOR_H
