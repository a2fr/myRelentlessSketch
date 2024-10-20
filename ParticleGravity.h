#ifndef PARTICLE_GRAVITY_H
#define PARTICLE_GRAVITY_H

#pragma once

#include "ParticleForceGenerator.h"

class ParticleGravity : public ParticleForceGenerator {
	Vector gravity; // Gravit�

	// Constructeur
public:
	ParticleGravity(const Vector& gravity);

	// Applique la force de gravit� � la particule
	virtual void updateForce(Particle* particle, float duration);

	// Get the vector of gravity
	Vector getGravity() const;
};

#endif