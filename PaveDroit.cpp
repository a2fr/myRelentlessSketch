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
    centerMass = position;
    initInertiaTensor();
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
    ofPushMatrix();
    ofTranslate(getPosition().getGlmVec());
    ofMultMatrix(getOrientation().normalize().toMatrix4().toOfMatrix4x4());  // Apply the box's rotation

    // Define the dimensions of the cuboid
    float length = 2.0f;
    float width = 1.0f;
    float height = 1.5f;

    // Define the vertices of the cuboid
    glm::vec3 vertices[8] = {
        glm::vec3(-length / 2, -height / 2, -width / 2), glm::vec3(length / 2, -height / 2, -width / 2),
        glm::vec3(length / 2, height / 2, -width / 2), glm::vec3(-length / 2, height / 2, -width / 2),
        glm::vec3(-length / 2, -height / 2, width / 2), glm::vec3(length / 2, -height / 2, width / 2),
        glm::vec3(length / 2, height / 2, width / 2), glm::vec3(-length / 2, height / 2, width / 2)
    };

    // Define the faces of the cuboid
    glm::vec3 faces[6][4] = {
        {vertices[0], vertices[1], vertices[2], vertices[3]},
        {vertices[1], vertices[5], vertices[6], vertices[2]},
        {vertices[5], vertices[4], vertices[7], vertices[6]},
        {vertices[4], vertices[0], vertices[3], vertices[7]},
        {vertices[0], vertices[1], vertices[5], vertices[4]},
        {vertices[3], vertices[2], vertices[6], vertices[7]}
    };

    // Define colors for each face
    ofColor colors[6] = {
        ofColor::red, ofColor::green, ofColor::blue,
        ofColor::yellow, ofColor::cyan, ofColor::magenta
    };

    // Draw each face with a different color
    for (int i = 0; i < 6; ++i) {
        drawFace(faces[i], colors[i]);
    }

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
