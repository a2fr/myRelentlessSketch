#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // Create a particle at a specific position, with a mass and radius
    Particle* p = new Particle(ofVec3f(0, 500, 0), 1.0f, 10.0f);  // Particle at position (0,500,0) with mass 1 and radius 10

    // Add the particle to the list of particles
    particles.push_back(p);

    // Create gravity force generator (gravity pointing downward)
    ParticleGravity* gravity = new ParticleGravity(ofVec3f(0, -9.81f, 0));

    // Add the particle and gravity generator to the force registry
    forceRegistry.add(p, gravity);
}

//--------------------------------------------------------------
void ofApp::update(){
    float deltaTime = ofGetLastFrameTime(); // Get time between frames

    // Update forces (apply gravity)
    forceRegistry.updateForces(deltaTime);

    // Update each particle's position based on the applied forces
    for (Particle* p : particles) {
        p->update(deltaTime);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    // Draw each particle
    for (Particle* p : particles) {
        p->draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // Optionally add new particles on key press
    if (key == ' ') {
        Particle* p = new Particle(ofVec3f(ofRandomWidth(), ofRandomHeight(), 0), ofRandom(0.5f, 2.0f), ofRandom(5, 20));
        particles.push_back(p);
        forceRegistry.add(p, new ParticleGravity(ofVec3f(0, -9.81f, 0)));  // Add gravity to new particle
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void exit() {
	// Clean up memory
	for (Particle* p : particles) {
		delete p;
	}
	particles.clear();
}