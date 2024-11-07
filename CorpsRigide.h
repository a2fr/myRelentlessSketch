// CorpsRigide.h
#ifndef CORPSRIGIDE_H
#define CORPSRIGIDE_H

#include "Vector.h"
#include "Quaternion.h"
#include "Matrix3.h"

class CorpsRigide {
public:
    double mass;
    double inertia;
    double inverseMass;
    double inverseInertia;

    Vector position;
    Vector velocity;
    Vector acceleration;
    Vector forceAccum;

    Quaternion orientation;
    Vector angularVelocity;
    Vector angularAcceleration;
    Vector torqueAccum;

    CorpsRigide();
    CorpsRigide(double mass, double inertia);

    void setMass(double m);
    void setInertia(double i);
    void addForce(const Vector& force);
    void addTorque(const Vector& torque);
    void integrate(double duration);

    double getMass() const;
    double getInverseMass() const;
    double getInertia() const;
    double getInverseInertia() const;

    void clearAccumulators();

    void setPosition(const Vector& pos);
    void setInertiaTensor(const Matrix3& inertiaTensor);
    const Vector& getPosition() const;
    const Quaternion& getOrientation() const;

    void setVelocity(const Vector& vel);
    void setAngularVelocity(const Vector& angVel);

    void applyForceAtPoint(const Vector& force, const Vector& point);
    void applyTorque(const Vector& torque);
};

#endif // CORPSRIGIDE_H
