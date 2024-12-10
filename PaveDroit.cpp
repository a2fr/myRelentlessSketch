#include "PaveDroit.h"

PaveDroit::PaveDroit() {
    position = Vector(0, 5, 0);
    velocity = Vector(0, 0, 0);
    acceleration = Vector(0, 0, 0);
    forceAccum = Vector(0, 0, 0);
    orientation = Quaternion(1, 0, 0, 0);
    angularVelocity = Vector(0, 0, 0);
    angularAcceleration = Vector(0, 0, 0);
    torqueAccum = Vector(0, 0, 0);
    setMass(1.0f);
    centerMass = Vector(1, 0, 0);
    initInertiaTensor();
    material.setShininess(64);
    material.setDiffuseColor(ofColor(200, 0, 0, 150));
    mesh.set(2.0f, 1.0f, 1.0f);
    updateBS();
    boundingSphere.setOwner(this);
}

PaveDroit::PaveDroit(double mass) {
    position = Vector(0, 5, 0);
    velocity = Vector(0, 0, 0);
    acceleration = Vector(0, 0, 0);
    forceAccum = Vector(0, 0, 0);
    orientation = Quaternion(1, 0, 0, 0);
    angularVelocity = Vector(0, 0, 0);
    angularAcceleration = Vector(0, 0, 0);
    torqueAccum = Vector(0, 0, 0);
    setMass(mass);
    centerMass = position;
    initInertiaTensor();
    updateBS();
    boundingSphere.setOwner(this);
}

PaveDroit::PaveDroit(const Vector& centerMass, double mass) {
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
    updateBS();
    boundingSphere.setOwner(this);
}

void PaveDroit::initInertiaTensor() {
    float length = 2.0f;
    float width = 1.0f;
    float height = 1.5f;
    double Im = (1.0f / 12.0f) * mass;
    Matrix3 inertiaTensor = Matrix3(
        Im * (width * width + height * height), 0, 0,
        0, Im * (length * length + height * height), 0,
        0, 0, Im * (length * length + width * width)
    );
    setInertiaTensor(inertiaTensor);
}

void PaveDroit::draw() {
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

    // Draw Bounding Sphere
    ofPushMatrix();
    ofSetColor(255, 0, 0, 100);  // Semi-transparent red
    ofNoFill();
    ofDrawSphere(boundingSphere.getCenter().getGlmVec(), boundingSphere.getRadius());
    ofPopMatrix();
}

void PaveDroit::drawFace(const glm::vec3 vertices[4], const ofColor& color) {
    ofSetColor(color);
    ofFill();
    ofBeginShape();
    for (int j = 0; j < 4; ++j) {
        ofVertex(vertices[j]);
    }
    ofEndShape(true);
}

void PaveDroit::updateBS() {
    // Dimensions du pavé droit
    float length = 2.0f; // Longueur (x)
    float width = 1.0f;  // Largeur (z)
    float height = 1.5f; // Hauteur (y)

    // Le rayon de la Bounding Sphere est la distance du centre à un sommet
    float bsRadius = 0.5f * sqrt(length * length + width * width + height * height);

    boundingSphere.setCenter(position);
    boundingSphere.setRadius(bsRadius);
}

const BoundingSphere& PaveDroit::getBS() const {
    return boundingSphere;
}