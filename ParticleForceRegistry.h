#ifndef ParticleForceRegistry_h
#define ParticleForceRegistry_h

#pragma once

#include "Particle.h"
#include "ParticleForceGenerator.h"

class ParticleForceRegistry
{
    public:
        struct ParticleForceRegistration {
            Particle* particle;
            ParticleForceGenerator* generator;
        };

    typedef std::vector<ParticleForceRegistration> Registry;
    Registry registry;

    void add(Particle* particle, ParticleForceGenerator* generator);

    void remove(Particle* particle, ParticleForceGenerator* generator);

    void clear();

    void updateForces(float duration);
};

#endif

