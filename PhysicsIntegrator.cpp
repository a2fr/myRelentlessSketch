// PhysicsIntegrator.cpp
#include "PhysicsIntegrator.h"


void PhysicsIntegrator::update(CorpsRigide& corps, double duration) {
    if (corps.getInverseMass() <= 0.0) return; // Immovable object

    // Update linear position and velocity
    Vector gravity = corps.isGravityActivated ? Vector(0, -9.81 * duration * 2, 0) : Vector(0, 0, 0);
    corps.acceleration = (gravity + corps.forceAccum) * corps.getInverseMass();
    corps.velocity += corps.acceleration * duration;
    corps.position += corps.velocity * duration;
    

    // Update rotational position and angular velocity
    Vector resultingAngularAcc = corps.torqueAccum * corps.getInverseInertia();
    corps.angularVelocity += resultingAngularAcc * duration;
    Quaternion angularVelocityQuat(0, corps.angularVelocity.x, corps.angularVelocity.y, corps.angularVelocity.z);
    corps.orientation += angularVelocityQuat * corps.orientation * duration * 0.5;
    corps.orientation.normalize();
    

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

    corps.updateBS();
}

void PhysicsIntegrator::addForce(CorpsRigide* corps, const Vector& force) {
    if (corps) {
        corps->forceAccum += force;
    }
}
