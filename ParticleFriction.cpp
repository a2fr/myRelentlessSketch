#include "ParticleFriction.h"

ParticleFriction::ParticleFriction(float staticCoeff, float k1, float k2, float normalForce)
    : staticFrictionCoefficient(staticCoeff), k1(k1), k2(k2) , normalForce(normalForce) {}

void ParticleFriction::updateForce(Particle* particle, float duration)
{
    // If the particle has infinite mass (zero inverse mass), do not apply friction
    if (particle->getInverseMasse() == 0.0f) return;

    // Get the velocity of the particle
    Vector velocity = particle->getVelocity();

    // If the velocity is close to zero, apply static friction
    if (velocity.getNorme() < 0.0001f) {
        // Static friction resists any motion; we apply the maximum possible static friction force
        Vector staticFrictionForce = -velocity.normalize() * staticFrictionCoefficient * normalForce;
        particle->addForce(staticFrictionForce);
    }
    else {
        // If the particle is moving, apply dynamic friction
        Vector dynamicFrictionForce = -velocity.normalize() * (k1*velocity.getNorme() +  k2*velocity.getNorme());
        particle->addForce(dynamicFrictionForce);
    }
}
