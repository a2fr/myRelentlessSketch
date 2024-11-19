#pragma once

#include "ofMain.h"
#include "CorpsRigide.h"
#include "Matrix3.h"

class PaveDroit : public CorpsRigide {
public:
    ofBoxPrimitive mesh;
public:
    PaveDroit();
    PaveDroit(double mass);
    PaveDroit(const Vector& centerMass, double mass);
    void draw() override;

private:
    void initInertiaTensor();
    void drawFace(const glm::vec3 vertices[4], const ofColor& color);
};
