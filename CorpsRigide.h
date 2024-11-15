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
    double inertia;
    double inverseMass;
    double inverseInertia;

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

    CorpsRigide();
    CorpsRigide(double mass, double inertia);
    CorpsRigide(const Vector& centerMass, double mass, double inertia);

    void setMass(double m);
    void setCenterMass(const Vector& centerMass);
    void setInertia(double i);
    void setPosition(const Vector& pos);
    void setInertiaTensor(const Matrix3& inertiaTensor);
    void setVelocity(const Vector& vel);
    void setAngularVelocity(const Vector& angVel);

    double getMass() const;
    double getInverseMass() const;
    double getInertia() const;
    double getInverseInertia() const;
    const Vector& getPosition() const;
    const Quaternion& getOrientation() const;

    void addForce(const Vector& force);
    void addTorque(const Vector& torque);

    void clearAccumulators();

    void applyForceAtPoint(const Vector& force, const Vector& point);
    void applyTorque(const Vector& torque);
};

#endif // CORPSRIGIDE_H

