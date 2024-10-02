#include "ParticleGravity.h"

void ParticleGravity::updateForce(Particle* particle, float duration)
{
	//If the particle has infinite mass (zero mass), do not apply force
    if (1/particle->getInverseMasse() <= 0.0f) {
        return;
    }

    Vector force = gravity * particle->getInverseMasse();

    particle->addForce(force);
}
