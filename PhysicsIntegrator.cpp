//// PhysicsIntegrator.cpp
//#include "PhysicsIntegrator.h"
//
//
//void PhysicsIntegrator::update(CorpsRigide& corps, double duration) {
//    if (corps.getInverseMass() <= 0.0) return; // Immovable object
//
//    // Update linear position and velocity
//    corps.position += corps.velocity * duration;
//    Vector resultingAcc = corps.acceleration + corps.forceAccum * corps.getInverseMass();
//    corps.velocity += resultingAcc * duration;
//
//    // Update rotational position and angular velocity
//    Quaternion angularVelocityQuat(0, corps.angularVelocity.x, corps.angularVelocity.y, corps.angularVelocity.z);
//    Quaternion deltaOrientation = angularVelocityQuat * corps.orientation * duration * 0.5;
//    corps.orientation += deltaOrientation;
//    corps.orientation.normalize();
//
//    Vector resultingAngularAcc = corps.angularAcceleration + corps.torqueAccum * corps.getInverseInertia();
//    corps.angularVelocity += resultingAngularAcc * duration;
//
//    // Clear accumulators for the next integration step
//    corps.clearAccumulators();
//}
//
//void PhysicsIntegrator::addForce(CorpsRigide* corps, const Vector& force) {
//    if (corps) {
//        corps->forceAccum += force;
//    }
//}
