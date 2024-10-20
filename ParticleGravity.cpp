#include "ParticleGravity.h"

ParticleGravity::ParticleGravity(const Vector& gravity)
{
	this->gravity = gravity;
}

void ParticleGravity::updateForce(Particle* particle, float duration)
{
	// If the particle has infinite mass (zero mass), do not apply force
	if (particle->getInverseMasse() == 0.0f) return;

	// Apply the force of gravity to the particle
	Vector force = gravity * 1/(particle->getInverseMasse());

    particle->addForce(force);
}

Vector ParticleGravity::getGravity() const
{
	return gravity;
}