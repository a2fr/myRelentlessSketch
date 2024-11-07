// CorpsRigide.cpp
#include "CorpsRigide.h"

CorpsRigide::CorpsRigide() : mass(1.0), inertia(1.0), position(0, 0, 0), velocity(0, 0, 0), acceleration(0, 0, 0),
forceAccum(0, 0, 0), orientation(1, 0, 0, 0), angularVelocity(0, 0, 0), angularAcceleration(0, 0, 0),
torqueAccum(0, 0, 0) {
    setMass(mass);
    setInertia(inertia);
}

CorpsRigide::CorpsRigide(double mass, double inertia) : position(0, 0, 0), velocity(0, 0, 0), acceleration(0, 0, 0),
forceAccum(0, 0, 0), orientation(1, 0, 0, 0), angularVelocity(0, 0, 0),
angularAcceleration(0, 0, 0), torqueAccum(0, 0, 0) {
    setMass(mass);
    setInertia(inertia);
}

void CorpsRigide::setMass(double m) {
    mass = m;
    inverseMass = (mass > 0.0) ? 1.0 / mass : 0.0;
}

void CorpsRigide::setInertia(double i) {
    inertia = i;
    inverseInertia = (inertia > 0.0) ? 1.0 / inertia : 0.0;
}

void CorpsRigide::addForce(const Vector& force) {
    forceAccum += force;
}

void CorpsRigide::addTorque(const Vector& torque) {
    torqueAccum += torque;
}

void CorpsRigide::integrate(double duration) {
    if (inverseMass <= 0.0) return; // Immovable object

    // Update linear position and velocity
    position += velocity * duration;
    Vector resultingAcc = acceleration + forceAccum * inverseMass;
    velocity += resultingAcc * duration;

    // Update rotational position and angular velocity
    Quaternion angularVelocityQuat(0, angularVelocity.x, angularVelocity.y, angularVelocity.z);
    Quaternion deltaOrientation = angularVelocityQuat * orientation * (0.5f * duration);
    orientation += deltaOrientation;
    orientation.normalize();

    Vector resultingAngularAcc = angularAcceleration + torqueAccum * inverseInertia;
    angularVelocity += resultingAngularAcc * duration;

    // Clear accumulators for the next integration step
    clearAccumulators();
}

double CorpsRigide::getMass() const {
    return mass;
}

double CorpsRigide::getInverseMass() const {
    return inverseMass;
}

double CorpsRigide::getInertia() const {
    return inertia;
}

double CorpsRigide::getInverseInertia() const {
    return inverseInertia;
}

void CorpsRigide::clearAccumulators() {
    forceAccum = Vector(0, 0, 0);
    torqueAccum = Vector(0, 0, 0);
}

void CorpsRigide::setPosition(const Vector& pos) {
    position = pos;
}

void CorpsRigide::setInertiaTensor(const Matrix3& inertiaTensor) {
    inertia = inertiaTensor.determinant();
    inverseInertia = (inertia > 0.0) ? 1.0 / inertia : 0.0;
}

const Vector& CorpsRigide::getPosition() const {
    return position;
}

const Quaternion& CorpsRigide::getOrientation() const {
    return orientation;
}

void CorpsRigide::setVelocity(const Vector& vel) {
    velocity = vel;
}

void CorpsRigide::setAngularVelocity(const Vector& angVel) {
    angularVelocity = angVel;
}

void CorpsRigide::applyForceAtPoint(const Vector& force, const Vector& point) {
    addForce(force);
    Vector offset = point - position;
    Vector torque = offset.cross(force);
    addTorque(torque);
}

void CorpsRigide::applyTorque(const Vector& torque) {
    addTorque(torque);
}
