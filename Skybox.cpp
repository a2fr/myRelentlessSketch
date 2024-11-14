#include "Skybox.h"

void Skybox::setup() {
    // Charger les textures pour chaque face de la skybox
    textures[0].load("skybox/clouds1_east.bmp");  // Face droite
    textures[1].load("skybox/clouds1_west.bmp");  // Face gauche
    textures[2].load("skybox/clouds1_up.bmp");    // Face haut
    textures[3].load("skybox/clouds1_down.bmp");  // Face bas
    textures[4].load("skybox/clouds1_north.bmp"); // Face avant
    textures[5].load("skybox/clouds1_south.bmp"); // Face arrière

    // Initialiser le mesh d'un cube pour la skybox
    skyboxMesh.setMode(OF_PRIMITIVE_TRIANGLES);

    int size = 2000;

    // Ajouter les sommets du cube (8 sommets pour un cube)
    skyboxMesh.addVertex(ofVec3f(-size, -size, -size));  // Face arrière
    skyboxMesh.addVertex(ofVec3f(size, -size, -size));
    skyboxMesh.addVertex(ofVec3f(size, size, -size));
    skyboxMesh.addVertex(ofVec3f(-size, size, -size));

    skyboxMesh.addVertex(ofVec3f(-size, -size, size));   // Face avant
    skyboxMesh.addVertex(ofVec3f(size, -size, size));
    skyboxMesh.addVertex(ofVec3f(size, size, size));
    skyboxMesh.addVertex(ofVec3f(-size, size, size));

    // Ajouter les indices pour dessiner les faces
    // Chaque face du cube est composée de 2 triangles (6 indices)
    skyboxMesh.addIndex(0); skyboxMesh.addIndex(1); skyboxMesh.addIndex(2);
    skyboxMesh.addIndex(0); skyboxMesh.addIndex(2); skyboxMesh.addIndex(3);

    skyboxMesh.addIndex(4); skyboxMesh.addIndex(5); skyboxMesh.addIndex(6);
    skyboxMesh.addIndex(4); skyboxMesh.addIndex(6); skyboxMesh.addIndex(7);

    skyboxMesh.addIndex(0); skyboxMesh.addIndex(1); skyboxMesh.addIndex(5);
    skyboxMesh.addIndex(0); skyboxMesh.addIndex(5); skyboxMesh.addIndex(4);

    skyboxMesh.addIndex(1); skyboxMesh.addIndex(2); skyboxMesh.addIndex(6);
    skyboxMesh.addIndex(1); skyboxMesh.addIndex(6); skyboxMesh.addIndex(5);

    skyboxMesh.addIndex(2); skyboxMesh.addIndex(3); skyboxMesh.addIndex(7);
    skyboxMesh.addIndex(2); skyboxMesh.addIndex(7); skyboxMesh.addIndex(6);

    skyboxMesh.addIndex(3); skyboxMesh.addIndex(0); skyboxMesh.addIndex(4);
    skyboxMesh.addIndex(3); skyboxMesh.addIndex(4); skyboxMesh.addIndex(7);

    // Ajouter les coordonnées UV pour chaque face
    // Définir les coordonnées UV pour chaque face de la skybox
    // UV pour la face avant
    skyboxMesh.addTexCoord(ofVec2f(0.0f, 0.0f));
    skyboxMesh.addTexCoord(ofVec2f(1.0f, 0.0f));
    skyboxMesh.addTexCoord(ofVec2f(1.0f, 1.0f));
    skyboxMesh.addTexCoord(ofVec2f(0.0f, 1.0f));

    // UV pour la face arrière
    skyboxMesh.addTexCoord(ofVec2f(0.0f, 0.0f));
    skyboxMesh.addTexCoord(ofVec2f(1.0f, 0.0f));
    skyboxMesh.addTexCoord(ofVec2f(1.0f, 1.0f));
    skyboxMesh.addTexCoord(ofVec2f(0.0f, 1.0f));

    // UV pour la face droite
    skyboxMesh.addTexCoord(ofVec2f(0.0f, 0.0f));
    skyboxMesh.addTexCoord(ofVec2f(1.0f, 0.0f));
    skyboxMesh.addTexCoord(ofVec2f(1.0f, 1.0f));
    skyboxMesh.addTexCoord(ofVec2f(0.0f, 1.0f));

    // UV pour la face gauche
    skyboxMesh.addTexCoord(ofVec2f(0.0f, 0.0f));
    skyboxMesh.addTexCoord(ofVec2f(1.0f, 0.0f));
    skyboxMesh.addTexCoord(ofVec2f(1.0f, 1.0f));
    skyboxMesh.addTexCoord(ofVec2f(0.0f, 1.0f));

    // UV pour la face haut
    skyboxMesh.addTexCoord(ofVec2f(0.0f, 0.0f));
    skyboxMesh.addTexCoord(ofVec2f(1.0f, 0.0f));
    skyboxMesh.addTexCoord(ofVec2f(1.0f, 1.0f));
    skyboxMesh.addTexCoord(ofVec2f(0.0f, 1.0f));

    // UV pour la face bas
    skyboxMesh.addTexCoord(ofVec2f(0.0f, 0.0f));
    skyboxMesh.addTexCoord(ofVec2f(1.0f, 0.0f));
    skyboxMesh.addTexCoord(ofVec2f(1.0f, 1.0f));
    skyboxMesh.addTexCoord(ofVec2f(0.0f, 1.0f));
}

void Skybox::draw() {
    ofEnableDepthTest();
    // Dessiner la skybox en appliquant les textures
    for (int i = 0; i < 6; ++i) {
        textures[i].getTexture().bind(); // Appliquer la texture sur la face
        skyboxMesh.draw();  // Dessiner le mesh avec la texture appliquée
        textures[i].getTexture().unbind(); // Libérer la texture après usage
    }
    ofDisableDepthTest();
}
