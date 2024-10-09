#pragma once
#include "ParticleForceGenerator.h"

class Friction : public ParticleForceGenerator {
public:
    Friction() {
        gravity = Vector(0, 9.81, 0);
        Uk = 0.7;
        Us = 0.8;
        K1 = 1;
        K2 = 0.8;
    }

    virtual void updateForce(Particle* particle, float duration);

private:
    Vector gravity;
    float Uk; // Coefficient de friction cinétique
    float Us; // Coefficient de friction statique
    float K1;
    float K2;
};

