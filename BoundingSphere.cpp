#include "BoundingSphere.h"
#include <cmath> // Pour std::sqrt

BoundingSphere::BoundingSphere() : center(Vector(0, 0, 0)), radius(0.0f), owner(nullptr) {}

BoundingSphere::BoundingSphere(const Vector& center, float radius, Vector pos)
    : center(center), radius(radius), owner(nullptr) {}

Vector BoundingSphere::getCenter() const {
    return center;
}

float BoundingSphere::getRadius() const {
    return radius;
}

void BoundingSphere::setCenter(const Vector& center) {
    this->center = center;
}

void BoundingSphere::setRadius(float radius) {
    this->radius = radius;
}

CorpsRigide* BoundingSphere::getOwner() const
{
    return owner;
}

void BoundingSphere::setOwner(CorpsRigide* obj)
{
    owner = obj;
}


void BoundingSphere::computeFromBox(const Vector& boxMin, const Vector& boxMax, const Vector& pos) {
    // Le centre est au milieu de la boîte
    center = pos;
    // Le rayon est la distance entre le centre et un des coins
    radius = (center - boxMax).getNorme();
}

bool BoundingSphere::intersects(const BoundingSphere& other) const {
    // Distance entre les centres des sphères
    float distance = (center - other.center).getNorme();
    // Comparaison avec la somme des rayons
    return distance <= (radius + other.radius);
}

bool BoundingSphere::contain(const BoundingSphere& other) const
{
    float distance = (center - other.center).getNorme();
    return distance <= (radius - other.radius);
}

bool BoundingSphere::contain(const Vector& point) const
{
    float distance = (center - point).getNorme();
    return distance <= radius;
}
