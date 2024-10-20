#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    titleFont.load("goodtimesrg.otf", 55);
    m_creditFont.load("goodtimesrg.otf", 20);

    currentState = MENU;

    // Define the start button rectangle
    startButton = new Button("START", ofRectangle(ofGetWidth() / 2 - 100, ofGetHeight() / 2 + 50, 200, 50), false);
    returnButton = new Button("RETURN", ofRectangle(ofGetWidth() - 120, 10, 100, 25), false);

    ground = new Ground(50, ofColor(255,255,255));

    // Create a particle at a specific position, with a mass and radius
    Particle* p = new Particle(Vector(100, 100, 0), 10, 10);
    // Add the particle to the list of particles
    particles.push_back(p);

    blob = MyBlob();

}

//--------------------------------------------------------------
void ofApp::update(){
    startButton->setPosition(ofRectangle(ofGetWidth() / 2 - 100, ofGetHeight() / 2 + 50, 200, 50));
    returnButton->setPosition(ofRectangle(ofGetWidth() - 120, 10, 100, 25));
    switch (currentState) {
    case MENU:
        updateMenu();
        break;
    case GAME:
        updateGame();
        break;
    }
}

void ofApp::updateMenu() {
    // Rien a faire
}

void ofApp::updateGame() {
    float deltaTime = ofGetLastFrameTime();
    for (Particle* p : particles) {
        // Add the particle and gravity generator to the force registry
        forceRegistry.add(p, gravity);
    }

    // Update forces (apply gravity)
    forceRegistry.updateForces(deltaTime);
    forceRegistry.clear();

    // Update each particle's position based on the applied forces
    for (Particle* p : particles) {
        p->update(deltaTime);
        p->clearAccum();
    }

    blob.update(deltaTime);

}

//--------------------------------------------------------------
void ofApp::draw(){
    switch (currentState) {
    case MENU:
        drawMenu();
        break;
    case GAME:
        drawGame();
        break;
    }
}

void ofApp::drawMenu() {
    ofBackground(0);

    // Draw the title
    ofSetColor(255);
    titleFont.drawString("SIMULATEUR DE BLOP", ofGetWidth() / 2 - titleFont.stringWidth("SIMULATEUR DE BLOP") / 2, ofGetHeight() / 2 - 50);

    startButton->Draw();

    ofSetColor(255);
    drawNames();
}

void ofApp::drawGame() {
    returnButton->Draw();
    ground->Draw();
    // Draw each particle
    for (Particle* p : particles) {
        p->draw();
    }

    blob.draw();
}

void ofApp::drawNames() {
    ofSetColor(255, 255, 255);
    m_creditFont.drawString("Hugo Brisset", 0, ofGetHeight() - 100);
    m_creditFont.drawString("Alexandre Belisle-Huard", 0, ofGetHeight() - 70);
    m_creditFont.drawString("Albin Horlaville", 0, ofGetHeight() - 40);
    m_creditFont.drawString("Alan Fresco", 0, ofGetHeight() - 10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ') {
        blob.addParticle(); 
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    if (currentState == MENU) {
        startButton->isHover(x, y);
    }
    else if (currentState == GAME) {
        returnButton->isHover(x, y);
    }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if (currentState == MENU && startButton->isHover(x, y)) {
        currentState = GAME;
    }
    else if (currentState == GAME) {
        if (returnButton->isHover(x, y)) {
            currentState = MENU;
        }
    }
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
    ground->resize();
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
//void ofApp::exit() {
//	// Clean up memory by deleting particles and force generators
//	for (Particle* p : particles) {
//		delete p;
//	}
//	particles.clear();
//	forceRegistry.clear();
//}






