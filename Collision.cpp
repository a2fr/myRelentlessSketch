// Collision.h
#pragma once
#include "Collision.h"

void Collision::detectAndResolveCollisions(std::vector<CorpsRigide*>& corpsObjects, OctreeNode* octree) {
    // Parcourir l'octree pour trouver les noeuds qui contiennent plusieurs objets
    std::vector<OctreeNode*> nodesToCheck;
    getNodesWithMultipleObjects(octree, nodesToCheck);

    // Vérification des collisions uniquement dans les noeuds ayant plusieurs objets
    for (OctreeNode* node : nodesToCheck) {
        for (size_t i = 0; i < node->m_sphere.size(); i++) {
            for (size_t j = i + 1; j < node->m_sphere.size(); j++) {
                BoundingSphere* sphere1 = node->m_sphere[i];
                BoundingSphere* sphere2 = node->m_sphere[j];

                // Vérifier si les deux spheres se chevauchent
                if (isCollision(sphere1, sphere2)) {
                    // Appliquer une force aux deux corps rigides
                    applyCollisionForce(sphere1->getOwner(), sphere2->getOwner());
                }
            }
        }
    }

    for (CorpsRigide* corps : corpsObjects) {
        detectCollisionWithGround(corps, 0.2f); // Coefficient de restitution pour le sol
    }
}

void Collision::getNodesWithMultipleObjects(OctreeNode* node, std::vector<OctreeNode*>& nodesToCheck) {
    // Si un noeud a plus d'un objet, on l'ajoute à la liste à vérifier
    if (node->m_sphere.size() > 1) {
        nodesToCheck.push_back(node);
    }

    // Si le noeud a des enfants, on les parcourt récursivement
    if (node->children[0] != nullptr) {
        for (int i = 0; i < 8; i++) {
            getNodesWithMultipleObjects(node->children[i], nodesToCheck);
        }
    }
}

bool Collision::isCollision(BoundingSphere* sphere1, BoundingSphere* sphere2) {
    // Calculer la distance entre les centres des deux spheres
    Vector center1 = sphere1->getCenter();
    Vector center2 = sphere2->getCenter();

    float distance = (center1 - center2).getNorme();
    float radiusSum = sphere1->getRadius() + sphere2->getRadius();

    return distance < radiusSum; // Collision si la distance est inférieure à la somme des rayons
}

void Collision::applyCollisionForce(CorpsRigide* corps1, CorpsRigide* corps2) {
    Vector direction = corps2->getPosition() - corps1->getPosition();
    direction.normalize();

    float overlap = (corps1->boundingSphere.getRadius() + corps2->boundingSphere.getRadius()) - (corps1->getPosition() - corps2->getPosition()).getNorme();

    float restitutionFactor = 0.5f;
    float forceMagnitude = overlap * restitutionFactor;

    // Appliquer une force opposée sur chaque corps rigide
    Vector force = direction * forceMagnitude;

    corps1->addForce(-force);  
    corps2->addForce(force); 

    //Vector normal = (corps2->getPosition() - corps1->getPosition()).normalize();

    //// Calculer la vitesse relative des deux corps rigides le long de la normale
    //Vector relativeVelocity = corps1->getVelocity() - corps2->getVelocity();
    //double velocityAlongNormal = produitScalaire(relativeVelocity, normal);

    //// Si la vitesse relative est positive, les corps s'éloignent, donc pas de collision
    //if (velocityAlongNormal > 0) return;

    //// Coefficient de restitution (0 = collision parfaitement élastique, 1 = inélastique)
    //double restitution = 1.0f;

    //// Calcul de l'impulsion
    //double impulseMagnitude = -(1 + restitution) * velocityAlongNormal;
    //impulseMagnitude /= corps1->getInverseMass() + corps2->getInverseMass();

    //// Appliquer l'impulsion aux deux corps rigides
    //Vector impulse = normal * impulseMagnitude;

    //// Calculer les nouvelles vitesses après la collision
    //corps1->setVelocity(corps1->getVelocity() + impulse * corps1->getInverseMass());
    //corps2->setVelocity(corps2->getVelocity() - impulse * corps2->getInverseMass());
}


void Collision::detectCollisionWithGround(CorpsRigide* corps, float restitution) {
    // Vérifier si la bounding sphere touche ou est en dessous du sol (y = 0)
    if (corps->boundingSphere.getCenter().y - corps->boundingSphere.getRadius() <= 0) {
        // Calculer la force de rebond
        Vector normal = Vector(0, 1, 0); // Normale du sol
        Vector relativeVelocity = corps->getVelocity();
        double velocityAlongNormal = produitScalaire(relativeVelocity, normal);

        // Ne rien faire si la sphère s'éloigne du sol
        if (velocityAlongNormal > 0) return;

        // Calcul de l'impulsion
        double impulseMagnitude = -(1 + restitution) * velocityAlongNormal;
        impulseMagnitude /= corps->getInverseMass();

        Vector impulse = normal * impulseMagnitude;

        // Appliquer l'impulsion au corps rigide
        corps->setVelocity(corps->getVelocity() + impulse);

        // Appliquer une correction de position si le corps est trop enfoncé dans le sol
        float penetration = corps->boundingSphere.getRadius() - corps->boundingSphere.getCenter().y;
        if (penetration > 0) {
            corps->setPosition(corps->getPosition() + normal * penetration);
        }
    }
}

