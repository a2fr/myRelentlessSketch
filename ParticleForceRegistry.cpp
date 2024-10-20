#include "ParticleForceRegistry.h"

// Ajout du registre
void ParticleForceRegistry::add(Particle* particle, ParticleForceGenerator* generator)
{
    ParticleForceRegistration registration;
    registration.particle = particle;
    registration.generator = generator;
    registry.push_back(registration);
}

// Retrait du registre
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

// Supprime les registres, pas les forces ni les générateurs
void ParticleForceRegistry::clear()
{
    registry.clear();
}

// Pour chaque élément du registre fait : x->generator->updateForce(x->particle, duration)
void ParticleForceRegistry::updateForces(float duration)
{
    Registry::iterator i = registry.begin();
    for (; i != registry.end(); i++) {
        i->generator->updateForce(i->particle, duration);
    }
}
