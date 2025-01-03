#include "ParticleSpring.h"

ParticleSpring::ParticleSpring(Particle* other, float springConstant, float restLength)
    : other(other), springConstant(springConstant), restLength(restLength) {}

void ParticleSpring::updateForce(Particle* particle, float duration) {
    // Calculate the vector from the particle to the other end of the spring
    Vector forceDirection = other->getPosition() - particle->getPosition();

    // Calculate the current length of the spring
    float length = forceDirection.getNorme();

    // Calculate the magnitude of the force
    float forceMagnitude = springConstant * (length - restLength);    

    // Apply the force to the particle
    if (length > 0.0f) {
        forceDirection = forceDirection.normalize();
        Vector force = forceDirection * forceMagnitude;
        particle->addForce(force);
    }
    //si trop �loign�: agit comme un cable
    float maxLength = 200.0f;
    if (length > maxLength) {
        Vector correction = forceDirection.normalize() * (length - maxLength);
        other->setPosition(other->getPosition() - correction * 0.5f);
        particle->setPosition(particle->getPosition() + correction * 0.5f);
    }

}
