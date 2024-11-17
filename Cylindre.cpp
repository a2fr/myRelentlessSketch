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
    centerMass = position;
    initInertiaTensor();
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
    ofPushMatrix();
    ofTranslate(getPosition().getGlmVec());
    ofMultMatrix(getOrientation().normalize().toMatrix4().toOfMatrix4x4());  // Apply the box's rotation

    // Define the properties of the cylinder
    float radius = 1.0f;
    float height = 2.0f;
    glm::vec3 baseCenter(0, -height / 2, 0);
    ofColor color = ofColor::blue;

    // Draw the cylinder
    drawCylinder(baseCenter, radius, height, color);
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
