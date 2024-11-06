#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    TestQuaternion testQ = TestQuaternion();
    testQ.runTests();
    TestMatrix3 testM3 = TestMatrix3();
    testM3.runTestMatrix3();
    TestMatrix4 testM4 = TestMatrix4();
    testM4.runTestMatrix4();

    titleFont.load("goodtimesrg.otf", 55);
    m_creditFont.load("goodtimesrg.otf", 20);
    nbParticleFont.load("goodtimesrg.otf", 15);

    currentState = MENU;

    // Define the start button rectangle
    startButton = new Button("START", ofRectangle(ofGetWidth() / 2 - 100, ofGetHeight() / 2 + 50, 200, 50), false);
    returnButton = new Button("RETURN", ofRectangle(ofGetWidth() - 120, 10, 100, 25), false);

    ground = Ground();
    world = World();

    blob = MyBlob();
    blob.setUpMyBlob();

    particleGreen = new Particle(Vector(ofGetWidth() - 100, 100, 0), 10, 0.0001f, ofColor::white);
    particleWhite = new Particle(Vector(ofGetWidth() - 100, 200, 0), 10, 0.1f, ofColor::white);

    world.addBlob(&blob);
    
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
    float deltaTime = ofGetLastFrameTime()*8;

    world.update(deltaTime);
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
    titleFont.drawString("SIMULATEUR DE BLOB", ofGetWidth() / 2 - titleFont.stringWidth("SIMULATEUR DE BLOB") / 2, ofGetHeight() / 2 - 50);

    startButton->Draw();

    ofSetColor(255);
    drawNames();
}

void ofApp::drawGame() {
    returnButton->Draw();
    world.draw();
    
    ofSetColor(ofColor::white);
    nbParticleFont.drawString("Nombre de particule du blob:  " + ofToString(blob.getParticleCount()), 20, 30);

    std::vector<Vector> groundPoints = ground.groundPoints;
    // Dessiner le sol à mi-hauteur de l'écran
    float groundY = static_cast<float>(3) * ofGetHeight() / 4;
	// Of draw rectangle to create a ground
    ofSetColor(255);
    
    ofSetColor(110, 59, 29);
    for (int i = 0; i < groundPoints.size() - 1; i++) {
        ofDrawLine(groundPoints[i].x, groundPoints[i].y, groundPoints[i + 1].x, groundPoints[i + 1].y);
    }

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
   if (key == 'a') {  // Vérifie si la touche espace est pressée
       blob.addParticle();
   }
   if (key == 'x') {  // Vérifie si la touche espace est pressée
       if (blob.getParticleCount() > 3) {
           MyBlob* newBlob = blob.split();
           world.addBlob(newBlob);
       }
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

void ofApp::resetGame() {
    // Clear the current particles
    //for (Particle* p : particles) {
    //    delete p;
    //}
    //particles.clear();

    //// Reinitialize particles
    //particleBlue = new Particle(Vector(1300, 400, 0), 10, 1.0f, ofColor::blue);
    //particleRed = new Particle(Vector(1000, 300, 0), 10, 1.0f, ofColor::red);
    //particleGreen = new Particle(Vector(450, 200, 0), 20, 1.0f, ofColor::green);
    //particleWhite = new Particle(Vector(550, 500, 0), 100, 0.3f, ofColor::white);
    //player = new Player(Vector(100, 100, 0), 10, 1.0f, ofColor::purple);

    //// Add the particles to the list
    //particles.push_back(particleBlue);
    //particles.push_back(particleRed);
    //particles.push_back(particleGreen);
    //particles.push_back(particleWhite);
    //particles.push_back(player);

    //// Reinitialize force generators
    //gravity = new ParticleGravity(Vector(0, 9.81, 0));
    //float springConstant = 0.2f;
    //float restLength = 200.0f;
    //springRed = new ParticleSpring(particleRed, springConstant, restLength);

    //float staticFrictionCoeff = 0.8f; // Increased static friction coefficient
    //float dynamicFrictionCoeff = 0.001f; // Increased dynamic friction coefficient
    //float normalForce = 100.0f; // Example normal force
    //friction = new ParticleFriction(staticFrictionCoeff, dynamicFrictionCoeff, normalForce);

    //// Clear the force registry
    //forceRegistry.clear();
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if (currentState == MENU && startButton->isHover(x, y)) {
        currentState = GAME;
    }
    else if (currentState == GAME) {
        if (returnButton->isHover(x, y)) {
			resetGame();
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