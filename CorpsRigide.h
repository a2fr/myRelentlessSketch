#ifndef CORPSRIGIDE_H
#define CORPSRIGIDE_H

#include "Vector.h"
#include "Quaternion.h"
#include <vector>
#include "Matrix3.h"

using namespace std;

class CorpsRigide {
public:
    double mass;
    Matrix3 inertia;
    double inverseMass;
    Matrix3 inverseInertia;

    Vector position;
    Vector centerMass; // Coordonnées relatives a la position de l'objet. Si le centre de l'objet est le centre de masse alors centreMasse = Vector(0, 0, 0)
    Vector velocity;
    Vector acceleration;
    Vector forceAccum;

    Quaternion orientation;
    Vector angularVelocity;
    Vector angularAcceleration;
    Vector torqueAccum;

    vector<Vector> trace;
    float tracePeriode = 50;
    int maxPointsInTrace = 20;
    int countTrace = 0;
    bool isGravityActivated = false;

    void setMass(double m);
    void setCenterMass(const Vector& centerMass);
    void setPosition(const Vector& pos);
    void setInertiaTensor(const Matrix3& inertiaTensor);
    void setVelocity(const Vector& vel);
    void setAngularVelocity(const Vector& angVel);

    double getMass() const;
    double getInverseMass() const;
    Matrix3 getInertia() const;
    Matrix3 getInverseInertia() const;
    const Vector& getPosition() const;
    const Quaternion& getOrientation() const;

    void addForce(const Vector& force);
    void addTorque(const Vector& torque);

    void clearAccumulators();

    void applyForceAtPoint(const Vector& force, const Vector& point);
    void applyTorque(const Vector& torque);

    virtual void draw() = 0;
};

#endif // CORPSRIGIDE_H

