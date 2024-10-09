#pragma once
#include "ofMain.h"

class Ground {
public:
    // Constructeur pour initialiser le sol avec une hauteur et une couleur
    Ground(float height, ofColor color) : m_height(height), m_color(color) {
        m_width = ofGetWidth();
        m_position = ofVec2f(0, ofGetHeight() - 200);
    }

    // Méthode pour dessiner le sol
    void Draw();

    // Méthode pour redimensionner le sol en cas de changement de taille de fenêtre
    void resize();

private:
    float m_width;
    float m_height;
    ofColor m_color;
    ofVec2f m_position;
};
