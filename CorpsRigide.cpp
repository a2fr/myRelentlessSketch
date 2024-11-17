#include "CorpsRigide.h"

void CorpsRigide::setMass(double m) {
    mass = m;
    inverseMass = (mass > 0.0) ? 1.0 / mass : 0.0;
}

void CorpsRigide::setCenterMass(const Vector& centerMass)
{
    this->centerMass = centerMass;
}

/*
void CorpsRigide::setInertia(double i) {
    inertia = i;
    inverseInertia = (inertia > 0.0) ? 1.0 / inertia : 0.0;
}
*/

void CorpsRigide::setPosition(const Vector& pos) {
    position = pos;
}

void CorpsRigide::setInertiaTensor(const Matrix3& inertiaTensor) {
    inertia = inertiaTensor;
    inverseInertia = inertia.inverse();
}

void CorpsRigide::setVelocity(const Vector& vel) {
    velocity = vel;
}

void CorpsRigide::setAngularVelocity(const Vector& angVel) {
    angularVelocity = angVel;

}

double CorpsRigide::getMass() const {
    return mass;
}

double CorpsRigide::getInverseMass() const {
    return inverseMass;
}

Matrix3 CorpsRigide::getInertia() const {
    return inertia;
}

Matrix3 CorpsRigide::getInverseInertia() const {
    return inverseInertia;
}

const Vector& CorpsRigide::getPosition() const {
    return position;
}

const Quaternion& CorpsRigide::getOrientation() const {
    return orientation;
}

void CorpsRigide::addForce(const Vector& force) {
    forceAccum += force;
}

void CorpsRigide::addTorque(const Vector& torque) {
    torqueAccum += torque;
}

void CorpsRigide::clearAccumulators() {
    forceAccum = Vector(0, 0, 0);
    torqueAccum = Vector(0, 0, 0);
}

void CorpsRigide::applyForceAtPoint(const Vector& force, const Vector& point) {
    isGravityActivated = true;
    addForce(force);
    forceAccum.afficher();
    Vector offset = point - (position + centerMass);
    Vector torque = produitVectoriel(offset, force) * 0.3;
    addTorque(torque);
}

void CorpsRigide::applyTorque(const Vector& torque) {
    addTorque(torque);
}
