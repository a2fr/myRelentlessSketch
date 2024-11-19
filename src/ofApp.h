#pragma once

#include "ofMain.h"
#include "..\PhysicsIntegrator.h"   // The physics integrator for handling forces
#include "..\Button.h"
#include "..\Skybox.h"
#include "..\Cube.h"
#include "..\Cylindre.h"
#include "..\PaveDroit.h"

enum GameState {
    MENU,
    GAME
};

class ofApp : public ofBaseApp {
public:
    // Standard openFrameworks methods
    void setup() override;
    void update() override;
    void draw() override;

    // Event handlers for interaction
    void mouseMoved(int x, int y) override;
    void mousePressed(int x, int y, int button) override;
    void keyPressed(int key) override;
    void keyReleased(int key) override;

    void drawMenu();
    void drawGame();
    void drawNames();
    void updateGame();
    void updateMenu();

private:
    GameState currentState;
    Button* startButton;
    Button* returnButton;
    ofTrueTypeFont titleFont;
    ofTrueTypeFont m_creditFont;
    ofTrueTypeFont launchForceFont;
    ofTrueTypeFont controlsFont;

    // Mouvement et vue du personnage
    ofEasyCam camera;

    ofLight pointLight;
    ofLight directionalLight;

    // Physics components
    PhysicsIntegrator physicsIntegrator; // Manages forces and updates on the rigid body

    // Helper methods
    void resetBox();                  // Reset the box's position and rotation
    void resetCamera();               // Reset the camera position and orientation

    // Game parameters
    float launchForce = 200;                // Magnitude of the launch force

    Skybox skybox;
    Cube& cube = Cube();
    Cylindre& cylindre = Cylindre();
    PaveDroit& paveDroit = PaveDroit();
};