#pragma once
#include "Vector.h" // Pour représenter les vecteurs

class CorpsRigide;

class BoundingSphere {
private:
    Vector center; // Centre de la sphère
    float radius;     // Rayon de la sphère
    CorpsRigide* owner;

public:
    BoundingSphere();
    BoundingSphere(const Vector& center, float radius, Vector pos);

    // Accesseurs
    Vector getCenter() const;
    float getRadius() const;

    // Mutateurs
    void setCenter(const Vector& center);
    void setRadius(float radius);

    CorpsRigide* getOwner() const;
    void setOwner(CorpsRigide* obj);

    // Méthodes
    void computeFromBox(const Vector& boxMin, const Vector& boxMax, const Vector& pos);
    bool intersects(const BoundingSphere& other) const;
    bool contain(const BoundingSphere& other) const;
    bool contain(const Vector& point) const;
};
