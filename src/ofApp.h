#pragma once

#include "ofMain.h"
#include "../Vector.h"
#include "../Particle.h"
#include "../Button.h"
#include "../ParticleForceRegistry.h"
#include "../ParticleGravity.h"
#include "../Ground.h"

enum GameState {
	MENU,
	GAME
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
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
		
		// Exit
		/*void exit();*/

private:

	GameState currentState;
	Button* startButton;
	Button* returnButton;
	ofTrueTypeFont titleFont;
	ofTrueTypeFont m_creditFont;

	Ground* ground;

	Particle m_particule;
	Vector m_initialPos;

	std::vector<Particle*> particles;    // List of particles
	ParticleForceRegistry forceRegistry;         // Force registry to apply forces to particles
	ParticleGravity* gravity = new ParticleGravity();
};
