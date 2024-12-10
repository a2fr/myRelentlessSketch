#pragma once

#include "ofMain.h"
#include "..\CorpsRigide.h"  
#include "..\PhysicsIntegrator.h"   // The physics integrator for handling forces
#include "..\Button.h"
#include "..\Cube.h"
#include "..\Cylindre.h"
#include "..\PaveDroit.h"
#include "..\World.h"

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

    // Helper methods
    void resetBox();                  // Reset the box's position and rotation
    void resetCamera();               // Reset the camera position and orientation

    // Game parameters
    float launchForce = 200;                // Magnitude of the launch force

    World* world;
};