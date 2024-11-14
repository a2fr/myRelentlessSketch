#pragma once

#include "ofMain.h"

class Skybox {
public:
    void setup();
    void draw();

private:
    ofMesh skyboxMesh;
    ofImage textures[6]; // On stocke les textures pour chaque face
};

