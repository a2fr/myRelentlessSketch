#pragma once

#include "ofMain.h"
#include "../Button.h"
#include "../ParticleForceRegistry.h"
#include "../ParticleGravity.h"
#include "../ParticleFriction.h"
#include "../ParticleSpring.h"
#include "../CollisionSystem.h"
#include "../World.h"
#include "../MyBlob.h"
#include "../Ground.h"



enum GameState {
    MENU,
    GAME
};

class ofApp : public ofBaseApp {

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);

	void resetGame();

    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

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
    ofTrueTypeFont nbParticleFont;

    Particle* particleGreen;
    Particle* particleWhite;

    Vector m_initialPos;

    World world;
    MyBlob blob;

    Ground ground;
};