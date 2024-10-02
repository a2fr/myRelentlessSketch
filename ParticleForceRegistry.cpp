#include "ParticleForceRegistry.h"

void ParticleForceRegistry::add(Particle* particle, ParticleForceGenerator* generator)
{
    ParticleForceRegistration registration;
    registration.particle = particle;
    registration.generator = generator;
    registry.push_back(registration);
}

void ParticleForceRegistry::remove(Particle* particle, ParticleForceGenerator* generator)
{
    Registry::iterator i = registry.begin();
    for (; i != registry.end(); i++) {
        if (i->particle == particle && i->generator == generator) {
            registry.erase(i);
            return;
        }
    }
}

void ParticleForceRegistry::clear()
{
    registry.clear();
}

void ParticleForceRegistry::updateForces(float duration)
{
    Registry::iterator i = registry.begin();
    for (; i != registry.end(); i++) {
        i->generator->updateForce(i->particle, duration);
    }
}
