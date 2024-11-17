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
    centerMass = position;
    initInertiaTensor();
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
    centerMass = position;
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
    ofPushMatrix();
    ofTranslate(getPosition().getGlmVec());
    ofMultMatrix(getOrientation().normalize().toMatrix4().toOfMatrix4x4());  // Apply the box's rotation

    // Define the vertices of the cube
    glm::vec3 vertices[8] = {
        glm::vec3(-1, -1, -1), glm::vec3(1, -1, -1), glm::vec3(1, 1, -1), glm::vec3(-1, 1, -1),
        glm::vec3(-1, -1, 1), glm::vec3(1, -1, 1), glm::vec3(1, 1, 1), glm::vec3(-1, 1, 1)
    };

    // Define the faces of the cube
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

void Cube::drawFace(const glm::vec3 vertices[4], const ofColor& color) {
    ofSetColor(color);
    ofFill();
    ofBeginShape();
    for (int j = 0; j < 4; ++j) {
        ofVertex(vertices[j]);
    }
    ofEndShape(true);
}
