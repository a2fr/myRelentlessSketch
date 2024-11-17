#pragma once

#include "CorpsRigide.h"
#include "ofMain.h"
#include "Matrix3.h"

class Cube : public CorpsRigide {
public:
    Cube();
    Cube(double mass);
    Cube(const Vector& centerMass, double mass);
    void draw() override;

private:
    void initInertiaTensor();
    void drawFace(const glm::vec3 vertices[4], const ofColor& color);
};
