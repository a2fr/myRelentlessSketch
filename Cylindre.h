#pragma once

#include "ofMain.h"
#include "CorpsRigide.h"
#include "Matrix3.h"

class Cylindre : public CorpsRigide {
public:
    Cylindre();
    Cylindre(double mass);
    Cylindre(const Vector& centerMass, double mass);
    void draw() override;

private:
    void initInertiaTensor();
    void drawCylinder(const glm::vec3& baseCenter, float radius, float height, const ofColor& color);
};
