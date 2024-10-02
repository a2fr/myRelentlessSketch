#ifndef PARTICLE_GRAVITY_H
#define PARTICLE_GRAVITY_H

#pragma once

#include "ParticleForceGenerator.h"
#include "Particle.h"
#include "Vector.h"

class ParticleGravity : public ParticleForceGenerator {
public:
    ParticleGravity(const Vector& gravity = Vector(0,9.81,0)) : gravity(gravity) {}

    virtual void updateForce(Particle* particle, float duration);

private:
    Vector gravity;
};

#endif