#include "Ground.h"

void Ground::setGroundPoints()
{
    groundPoints.clear();

    // Pente l�g�rement inclin�e
    groundPoints.push_back(Vector(0, ofGetHeight() * 0.75f, 0));                  // Point de d�part
    groundPoints.push_back(Vector(ofGetWidth() * 0.4f, ofGetHeight() * 0.60f, 0)); // Fin de la pente l�g�re

    // Pente fortement inclin�e
    groundPoints.push_back(Vector(ofGetWidth() * 0.6f, ofGetHeight() * 0.90f, 0));  // Fin de la pente raide

    // Sol plat 
    groundPoints.push_back(Vector(ofGetWidth() * 0.8f, ofGetHeight() * 0.90f, 0));  // Fin du sol plat

    // Escalier de trois marches
    groundPoints.push_back(Vector(ofGetWidth() * 0.81f, ofGetHeight() * 0.80f, 0)); 
    groundPoints.push_back(Vector(ofGetWidth() * 0.9f, ofGetHeight() * 0.80f, 0));

    groundPoints.push_back(Vector(ofGetWidth() * 0.91f, ofGetHeight() * 0.70, 0));
    groundPoints.push_back(Vector(ofGetWidth(), ofGetHeight() * 0.70, 0));
}


