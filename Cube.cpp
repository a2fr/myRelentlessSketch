#include "Cube.h"

Cube::Cube(){
    position = Vector(0, 5, 0);
    velocity = Vector(0, 0, 0);
    acceleration = Vector(0, 0, 0);
    forceAccum = Vector(0, 0, 0);
    orientation = Quaternion(1, 0, 0, 0);
    angularVelocity = Vector(0, 0, 0);
    angularAcceleration = Vector(0, 0, 0);
    torqueAccum = Vector(0, 0, 0);
    setMass(1);
    centerMass = Vector(0.5, 0.5, 0.5);
    initInertiaTensor();
    material.setShininess(64);
    material.setDiffuseColor(ofColor(200, 0, 0, 150));
    mesh.set(2.0f);
}

Cube::Cube(double mass){
    position = Vector(0, 5, 0);
    velocity = Vector(0, 0, 0);
    acceleration = Vector(0, 0, 0);
    forceAccum = Vector(0, 0, 0);
    orientation = Quaternion(1, 0, 0, 0);
    angularVelocity = Vector(0, 0, 0);
    angularAcceleration = Vector(0, 0, 0);
    torqueAccum = Vector(0, 0, 0);
    setMass(mass);
    centerMass = Vector(0, 0, 0);
    initInertiaTensor();
}

Cube::Cube(const Vector& centerMass, double mass){
    position = Vector(0, 5, 0);
    velocity = Vector(0, 0, 0);
    acceleration = Vector(0, 0, 0);
    forceAccum = Vector(0, 0, 0);
    orientation = Quaternion(1, 0, 0, 0);
    angularVelocity = Vector(0, 0, 0);
    angularAcceleration = Vector(0, 0, 0);
    torqueAccum = Vector(0, 0, 0);
    setMass(mass);
    this->centerMass = centerMass;
    initInertiaTensor();
}

void Cube::initInertiaTensor() {
    float sideLength = 2.0f;
    double Im = (1.0f / 6.0f) * mass * sideLength * sideLength;
    Matrix3 inertiaTensor = Matrix3(
        Im * 2, 0, 0,
        0, Im * 2, 0,
        0, 0, Im * 2
    );
    setInertiaTensor(inertiaTensor);
}

void Cube::draw() {
    // Mesh
    ofPushMatrix();
    ofTranslate(getPosition().getGlmVec());
    ofMultMatrix(getOrientation().normalize().toMatrix4().toOfMatrix4x4());  // Apply the box's rotation

    material.begin();
    mesh.draw();
    material.end();

    // centerMass
    ofTranslate(centerMass.getGlmVec());

    ofSetColor(0);
    ofDrawSphere(0.1f);

    ofPopMatrix();
}

void Cube::drawFace(const glm::vec3 vertices[4], const ofColor& color) {
    ofSetColor(color);
    ofFill();
    ofBeginShape();
    for (int j = 0; j < 4; ++j) {
        ofVertex(vertices[j]);
    }
    ofEndShape(true);
}
