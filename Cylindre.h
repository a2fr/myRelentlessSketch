#pragma once

#include "ofMain.h"
#include "CorpsRigide.h"
#include "Matrix3.h"

class Cylindre : public CorpsRigide {
public:
    ofCylinderPrimitive mesh;
public:
    Cylindre();
    Cylindre(double mass);
    Cylindre(const Vector& centerMass, double mass);
    void draw() override;

    void updateBS() override;
    const BoundingSphere& getBS() const override;

private:
    void initInertiaTensor();
    void drawCylinder(const glm::vec3& baseCenter, float radius, float height, const ofColor& color);


};
