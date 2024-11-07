#pragma once

#include "ofMain.h"
#include "..\CorpsRigide.h"         // Your rigid body class
#include "..\PhysicsIntegrator.h"   // The physics integrator for handling forces
#include "..\Button.h"

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

    // Camera for 3D perspective
    ofEasyCam camera;

    // Physics components
    CorpsRigide box;                  // Rigid body for the box
    PhysicsIntegrator physicsIntegrator; // Manages forces and updates on the rigid body

    // Helper methods
    void resetBox();                  // Reset the box's position and rotation
	void resetCamera();               // Reset the camera position and orientation

    // Game parameters
    float launchForce;                // Magnitude of the launch force
    Vector gravity;                   // Gravity vector
    float torqueFactor;               // Scaling factor for applied torque
};
