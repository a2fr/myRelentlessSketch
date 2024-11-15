// PhysicsIntegrator.cpp
#include "PhysicsIntegrator.h"


void PhysicsIntegrator::update(CorpsRigide& corps, double duration) {
    if (corps.getInverseMass() <= 0.0) return; // Immovable object

    // Update linear position and velocity
    Vector gravity = corps.isGravityActivated ? Vector(0, -9.81 * duration, 0) : Vector(0, 0, 0);
    corps.acceleration = (gravity + corps.forceAccum) * corps.getInverseMass();
    corps.position += corps.velocity * duration + corps.acceleration * duration * duration * 0.5;
    corps.velocity += corps.acceleration * duration;

    // Update rotational position and angular velocity
    Quaternion angularVelocityQuat(0, corps.angularVelocity.x, corps.angularVelocity.y, corps.angularVelocity.z);
    Quaternion deltaOrientation = angularVelocityQuat * corps.orientation * duration * 0.5;
    corps.orientation += deltaOrientation;
    corps.orientation.normalize();

    Vector resultingAngularAcc = corps.angularAcceleration + corps.torqueAccum * corps.getInverseInertia();
    corps.angularVelocity += resultingAngularAcc * duration;

    // Clear accumulators for the next integration step
    corps.clearAccumulators();

    // Create trace
    if (corps.countTrace > corps.tracePeriode ) {
        corps.countTrace = 0;
        if (corps.trace.size() == corps.maxPointsInTrace) {
            vector<Vector> newTab;
            bool skipFirst = false;
            for (const Vector& v : corps.trace) {
                if (!skipFirst) {
                    skipFirst = true;
                    continue;
                }
                newTab.push_back(v);
            }
            corps.trace = newTab;
        }
        corps.trace.push_back(Vector(corps.getPosition()));
    }
    corps.countTrace++;
}

void PhysicsIntegrator::addForce(CorpsRigide* corps, const Vector& force) {
    if (corps) {
        corps->forceAccum += force;
    }
}
