#pragma once

#include "Particle.h"
#include <vector>

// Forward declaration of Particle class
class Particle;

// Abstract base class for force generators
class ForceGenerator {
public:
    virtual void applyForce(Particle& particle, float duration) = 0;
    virtual ~ForceGenerator() = default;
};

// Registry to manage force generators and their associated particles
class ForceRegistry {
public:
    struct ForceRegistration {
        Particle* particle;
        ForceGenerator* generator;
    };

    void add(Particle* particle, ForceGenerator* generator);
    void remove(Particle* particle, ForceGenerator* generator);
    void clear();
    void updateForces(float duration);

private:
    std::vector<ForceRegistration> registry;
};
