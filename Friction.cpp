#include "Friction.h"

void Friction::updateForce(Particle* particle, float duration)
{
	Vector velocity = particle->getVelocity();
	Vector force;

	if (velocity.getNorme() < 0.1) { // Arrondis a zero si la norme est en dessous de 0.1
		// Cas statique
		force = gravity * -1;
	}
	else { 
		// Cas cinétique
		float norme = velocity.getNorme();
		force = velocity.getNormalize() * -1 * (K1 * norme + K2 * norme * norme);
	}

	particle->addForce(force);
}
