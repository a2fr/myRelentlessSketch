#include "CollisionSystem.h"
#include "Vector.h"

bool CollisionSystem::checkForCollision(const Particle& p1, const Particle& p2) {
    Vector distanceVector = p1.getPosition() - p2.getPosition();
    double distance = distanceVector.getNorme();
    double sumOfRadii = p1.getWidth() + p2.getWidth();
    return distance <= sumOfRadii;
}

void CollisionSystem::resolveCollision(Particle& p1, Particle& p2) {
    // Vérifier si les particules appartiennent au même blob
    if (p1.getRefBlob() == p2.getRefBlob()) {
        // Les deux particules appartiennent au même blob, procéder à la résolution de collision
        Vector normal = (p1.getPosition() - p2.getPosition()).normalize();
        Vector relativeVelocity = p1.getVelocity() - p2.getVelocity();
        double velocityAlongNormal = produitScalaire(relativeVelocity, normal);

        // Only resolve if particles are moving towards each other
        if (velocityAlongNormal > 0) return;

        double restitution = 1.0f; // Coefficient de restitution (vous pouvez ajuster cette valeur)
        double impulseMagnitude = -(1 + restitution) * velocityAlongNormal;
        impulseMagnitude /= p1.getInverseMasse() + p2.getInverseMasse();

        Vector impulse = normal * impulseMagnitude;

        // Appliquer les impulsions
        p1.setVelocity(p1.getVelocity() + impulse * p1.getInverseMasse());
        p2.setVelocity(p2.getVelocity() - impulse * p2.getInverseMasse());
    }
    else {
        // Les particules appartiennent à des blobs différents
        MyBlob* blob1 = p1.getRefBlob(); // Blob de la première particule
        MyBlob* blob2 = p2.getRefBlob(); // Blob de la deuxième particule

        if (blob1 && blob2) {
            // Appeler la méthode collapse en passant l'autre blob
            blob1->collapse(*blob2); // Fusionner blob1 avec blob2
        }
    }
}

bool CollisionSystem::checkForStationaryCollision(const Particle& p, const Vector& gravity) {
    Vector expectedAcceleration = gravity * p.getInverseMasse();
    return (p.getAcceleration() - expectedAcceleration).getNorme() < 0.1; // Small threshold for comparison
}


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
        //Impulsions
        p.setVelocity(Vector(-p.getVelocity().getX(), p.getVelocity().getY(), p.getVelocity().getZ()));

        return;
    }
    else if (i >= groundPoints.size()) { // Collision avec le mur de droite
        // Collision with the right wall
        p.setPosition(Vector(p.getPosition().getX() - p.getWidth(), p.getPosition().y, p.getPosition().z));

        //Impulsions
        p.setVelocity(Vector(-p.getVelocity().getX(), p.getVelocity().getY(), p.getVelocity().getZ()));
        return;
    }
    else { // collision avec le sol
        // Trouver la hauteur du terrain sur la portion i-1, i.
        float deltaX = groundPoints[i].x - groundPoints[i - 1].x;
        float deltaY = groundPoints[i].y - groundPoints[i - 1].y;

        float a = deltaY / deltaX;
        float b = groundPoints[i].y - a * groundPoints[i].x;
        float groundY = a * p.getPosition().x + b;

        if (p.getPosition().getY() + p.getWidth() >= groundY) {
            // Interpenetration
            p.setPosition(Vector(p.getPosition().getX(), groundY - p.getWidth(), p.getPosition().getZ()));

            // Si la pente est nulle (sol plat), on ne fait que l'interpénétration, pas de vélocité modifiée
            if (a == 0) {
                return; // Sol plat, on s'arrête ici
            }

            // Calculer la vélocité parallèle et perpendiculaire à la pente si la pente n'est pas nulle
            Vector velocity = p.getVelocity();
            Vector tangent = Vector(1, a, 0).normalize();
            Vector normal = Vector(-1 / a, 1, 0).normalize();

            // Composante de la vélocité dans la direction normale (perpendiculaire)
            float velocityNormal = produitScalaire(velocity, normal);

            // Composante de la vélocité dans la direction tangentielle (glissement)
            float velocityTangent = produitScalaire(velocity, tangent);

            // Réduire la vélocité normale (réaction de l'impact) et tangente (friction dynamique)
            float restitution = 0.1; // Facteur de restitution pour amortir le rebond
            float dynamicFriction = 0.01; // Coefficient de friction dynamique

            // Appliquer les changements de vélocité
            Vector newVelocity = tangent * (velocityTangent * (1 - dynamicFriction)) - normal * (velocityNormal * restitution);
            p.setVelocity(newVelocity);
        }
    }
}


void CollisionSystem::detectAndResolveCollisions(std::vector<Particle*>& particles, float deltaTime, ParticleGravity* gravity, float dynamicFrictionCoeff, float normalForce, float k1, float k2, float staticFrictionCoefficient) {

    float groundY = static_cast<float>(3) * ofGetHeight() / 4; // Ground is at y = groundY

	Vector gravityForce = gravity->getGravity();

    std::vector<Vector> groundPoints = ground.groundPoints;

    for (size_t i = 0; i < particles.size(); ++i) {
        for (size_t j = i + 1; j < particles.size(); ++j) {
            if (checkForCollision(*particles[i], *particles[j])) {
                resolveCollision(*particles[i], *particles[j]);
                enforceCableConstraint(*particles[i], *particles[j], 100);
            }
        }

        //if (!checkForStationaryCollision(*particles[i], gravityForce)) {
            // Check for ground collision
            checkForGroundCollision(*particles[i], groundPoints, dynamicFrictionCoeff, normalForce);
        //}
     }
}

