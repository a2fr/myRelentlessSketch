#include "CollisionSystem.h"
#include "Vector.h"

bool CollisionSystem::checkForCollision(const Particle& p1, const Particle& p2) {
    Vector distanceVector = p1.getPosition() - p2.getPosition();
    double distance = distanceVector.getNorme();
    double sumOfRadii = p1.getWidth() + p2.getWidth();
    return distance <= sumOfRadii;
}

void CollisionSystem::resolveCollision(Particle& p1, Particle& p2) {
    Vector normal = (p1.getPosition() - p2.getPosition()).normalize();
    Vector relativeVelocity = p1.getVelocity() - p2.getVelocity();
    double velocityAlongNormal = produitScalaire(relativeVelocity, normal);

    // Only resolve if particles are moving towards each other
    if (velocityAlongNormal > 0) return;

    double restitution = 1.0f; // Coefficient of restitution (you can adjust this value)
    double impulseMagnitude = -(1 + restitution) * velocityAlongNormal;
    impulseMagnitude /= p1.getInverseMasse() + p2.getInverseMasse();

    Vector impulse = normal * impulseMagnitude;

    // Apply impulses
    p1.setVelocity(p1.getVelocity() + impulse * p1.getInverseMasse());
    p2.setVelocity(p2.getVelocity() - impulse * p2.getInverseMasse());
}

bool CollisionSystem::checkForStationaryCollision(const Particle& p, const Vector& gravity) {
    Vector expectedAcceleration = gravity * p.getInverseMasse();
    return (p.getAcceleration() - expectedAcceleration).getNorme() < 0.01; // Small threshold for comparison
}

// Example of enforcing cable and steel rod constraints
void CollisionSystem::enforceCableConstraint(Particle& p1, Particle& p2, float maxLength) {
    Vector distanceVector = p1.getPosition() - p2.getPosition();
    double distance = distanceVector.getNorme();
    if (distance > maxLength) {
        Vector correction = distanceVector.normalize() * (distance - maxLength);
        p1.setPosition(p1.getPosition() - correction * 0.5f);
        p2.setPosition(p2.getPosition() + correction * 0.5f);
    }
}

void CollisionSystem::enforceSteelRodConstraint(Particle& p1, Particle& p2, float fixedLength) {
    Vector distanceVector = p1.getPosition() - p2.getPosition();
    double distance = distanceVector.getNorme();
    if (distance != fixedLength) {
        Vector correction = distanceVector.normalize() * (distance - fixedLength);
        p1.setPosition(p1.getPosition() - correction * 0.5f);
        p2.setPosition(p2.getPosition() + correction * 0.5f);
    }
}

void CollisionSystem::checkForGroundCollision(Particle& p, std::vector<Vector> groundPoints, float dynamicFrictionCoeff, float normalForce) {
    // Trouver entre quels points se trouve la particule. Décider si elle est au dessus ou en dessous la droite formée par les deux points.
    int i = 0;
    while (groundPoints[i].x < p.getPosition().x) {
        i++;
        if (i >= groundPoints.size()) {
            break;
        }
    }
    
    if (i == 0) { // Collision avec le mur de gauche
        // Collision with the left wall
        p.setPosition(Vector(p.getPosition().getX() + p.getWidth(), p.getPosition().y, p.getPosition().z));

        // Nullify the vertical velocity
        p.setVelocity(Vector(-p.getVelocity().getX(), p.getVelocity().getY(), p.getVelocity().getZ()));

        // Apply Vertical friction
        float frictionForce = -p.getVelocity().getY() * dynamicFrictionCoeff * normalForce;
        p.addForce(Vector(frictionForce, 0, 0));
        return;
    }
    else if (p.getPosition().x >= ofGetWidth()) { // Collision avec le mur de droite
        // Collision with the right wall
        p.setPosition(Vector(p.getPosition().getX() - p.getWidth(), p.getPosition().y, p.getPosition().z));

        // Nullify the vertical velocity
        p.setVelocity(Vector(-p.getVelocity().getX(), p.getVelocity().getY(), p.getVelocity().getZ()));

        // Apply Vertical friction
        float frictionForce = -p.getVelocity().getY() * dynamicFrictionCoeff * normalForce;
        p.addForce(Vector(frictionForce, 0, 0));
        return;
    }
    else { // Peut être collision avec le sol
        // Trouver la hauteur du terrain sur la portion i-1, i.
        float a = (groundPoints[i].y - groundPoints[i - 1].y) / (groundPoints[i].x - groundPoints[i - 1].x);
        float b = groundPoints[i].y - a * groundPoints[i].x;
        float groundY = a * p.getPosition().x + b;

        if (p.getPosition().getY() + p.getWidth() >= groundY) {
            // Collision with the ground
            p.setPosition(Vector(p.getPosition().getX(), groundY - p.getWidth(), p.getPosition().getZ()));

            // Nullify the vertical velocity
            p.setVelocity(Vector(p.getVelocity().getX(), 0, p.getVelocity().getZ()));

            // Apply horizontal friction
            float frictionForce = -p.getVelocity().getX() * dynamicFrictionCoeff * normalForce;
            p.addForce(Vector(frictionForce, 0, 0));
        }
    }
}


void CollisionSystem::detectAndResolveCollisions(std::vector<Particle*>& particles, float deltaTime, ParticleGravity* gravity, float dynamicFrictionCoeff, float normalForce) {

    float groundY = static_cast<float>(3) * ofGetHeight() / 4; // Ground is at y = groundY

	Vector gravityForce = gravity->getGravity();

    std::vector<Vector> groundPoints = {
        Vector(0, ofGetHeight() * 0.75f, 0),
        Vector(ofGetWidth() * 0.25f, ofGetHeight() * 0.65f, 0),
        Vector(ofGetWidth() * 0.5f, ofGetHeight() * 0.75f, 0),
        Vector(ofGetWidth() * 0.75f, ofGetHeight() * 0.65f, 0),
        Vector(ofGetWidth(), ofGetHeight() * 0.75f, 0)
    };

    for (size_t i = 0; i < particles.size(); ++i) {
        for (size_t j = i + 1; j < particles.size(); ++j) {
            if (checkForCollision(*particles[i], *particles[j])) {
                resolveCollision(*particles[i], *particles[j]);
            }
        }


        // Check for ground collision
        checkForGroundCollision(*particles[i], groundPoints, dynamicFrictionCoeff, normalForce);
    }
}
