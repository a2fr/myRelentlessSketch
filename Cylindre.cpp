#include "Cylindre.h"

Cylindre::Cylindre() {
    position = Vector(0, 5, 0);
    velocity = Vector(0, 0, 0);
    acceleration = Vector(0, 0, 0);
    forceAccum = Vector(0, 0, 0);
    orientation = Quaternion(1, 0, 0, 0);
    angularVelocity = Vector(0, 0, 0);
    angularAcceleration = Vector(0, 0, 0);
    torqueAccum = Vector(0, 0, 0);
    setMass(1.0f);
    centerMass = Vector(0, 1, 0.5);
    initInertiaTensor();
    material.setShininess(64);
    material.setDiffuseColor(ofColor(200, 0, 0, 150));
    mesh.set(1, 2);
    updateBS();
    boundingSphere.setOwner(this);
}

Cylindre::Cylindre(double mass) {
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

Cylindre::Cylindre(const Vector& centerMass, double mass) {
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

void Cylindre::initInertiaTensor() {
    float radius = 1.0f;
    float height = 2.0f;
    Matrix3 inertiaTensor = Matrix3(
        mass * (0.25f * radius * radius + 0.083333f * height * height), 0, 0,
        0, mass * (0.25f * radius * radius + 0.083333f * height * height), 0,
        0, 0, mass * 0.5f * radius * radius
    );
   setInertiaTensor(inertiaTensor);
}

void Cylindre::draw() {
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
    ofSetColor(0, 0, 255, 100);  // Semi-transparent blue
    ofNoFill();
    ofDrawSphere(boundingSphere.getCenter().getGlmVec(), boundingSphere.getRadius());
    ofPopMatrix();
}

void Cylindre::drawCylinder(const glm::vec3& baseCenter, float radius, float height, const ofColor& color) {
    ofSetColor(color);
    ofFill();

    // Draw the base circle
    ofBeginShape();
    for (int i = 0; i <= 100; ++i) {
        float angle = ofMap(i, 0, 100, 0, TWO_PI);
        glm::vec3 point(radius * cos(angle), baseCenter.y, radius * sin(angle));
        ofVertex(point);
    }
    ofEndShape(true);

    // Draw the top circle
    ofBeginShape();
    for (int i = 0; i <= 100; ++i) {
        float angle = ofMap(i, 0, 100, 0, TWO_PI);
        glm::vec3 point(radius * cos(angle), baseCenter.y + height, radius * sin(angle));
        ofVertex(point);
    }
    ofEndShape(true);

    // Draw the sides
    ofBeginShape();
    for (int i = 0; i <= 100; ++i) {
        float angle = ofMap(i, 0, 100, 0, TWO_PI);
        glm::vec3 basePoint(radius * cos(angle), baseCenter.y, radius * sin(angle));
        glm::vec3 topPoint(radius * cos(angle), baseCenter.y + height, radius * sin(angle));
        ofVertex(basePoint);
        ofVertex(topPoint);
    }
    ofEndShape();
}


void Cylindre::updateBS() {
    // La Bounding Sphere est définie avec son centre à la position actuelle et son rayon
    float radius = 1.0f; // Rayon du cylindre 
    float height = 2.0f; // Hauteur du cylindre

    // Le rayon de la Bounding Sphere est la distance entre le centre et le point le plus éloigné
    float bsRadius = sqrt(radius * radius + (height / 2) * (height / 2));

    boundingSphere.setCenter(position);
    boundingSphere.setRadius(bsRadius);
}

const BoundingSphere& Cylindre::getBS() const {
    return boundingSphere;
}
