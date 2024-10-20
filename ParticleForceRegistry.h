#ifndef ParticleForceRegistry_h
#define ParticleForceRegistry_h

#pragma once

#include "ParticleForceGenerator.h"

class ParticleForceRegistry
{
    public:
		// Enregistrement d'une force et de son générateur
        struct ParticleForceRegistration {
            Particle* particle;
            ParticleForceGenerator* generator;
        };

    // Le type registre est un tableau dynamique d'enregistrements
    typedef std::vector<ParticleForceRegistration> Registry;
    Registry registry;

	// Ajout/Retrait du registre
    void add(Particle* particle, ParticleForceGenerator* generator);
    void remove(Particle* particle, ParticleForceGenerator* generator);

	// Supprime les registres, pas les forces ni les générateurs
    void clear();

	// Pour chaque élément du registre fait : x->generator->updateForce(x->particle, duration)
    void updateForces(float duration);
};

/* Donc, à chaque frame :
1) Ajouter le force au registre
2) updateForces()
3) clear()
4) Intégrer chague particule (et vider l'accumulateur)
*/

#endif

