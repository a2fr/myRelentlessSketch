#pragma once

#include "ofMain.h"
#include "..\Particle.h"
#include "..\ForceGenerator.h"
#include "..\ParticleGravity.h"

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
		
		void exit();


private:
	std::vector<Particle*> particles;    // List of particles
	ForceRegistry forceRegistry;         // Force registry to apply forces to particles
};
