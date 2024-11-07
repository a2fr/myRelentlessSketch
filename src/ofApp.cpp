#include "ofApp.h"

// Settings for the shooting game
float launchForce = 20.0f;
Vector launchPosition(0, 0, 0);
Vector gravity(0, -9.81f, 0);
float torqueFactor = 0.1f;

// Setup the application window and scene
void ofApp::setup() {
    titleFont.load("goodtimesrg.otf", 55);
    m_creditFont.load("goodtimesrg.otf", 20);
    // Load a font for displaying text
    launchForceFont.load("goodtimesrg.otf", 20);

    currentState = MENU;

    // Define the start button rectangle
    startButton = new Button("START", ofRectangle(ofGetWidth() / 2 - 100, ofGetHeight() / 2 + 50, 200, 50), false);
    returnButton = new Button("RETURN", ofRectangle(ofGetWidth() - 120, 10, 100, 25), false);
    ofBackground(30, 30, 30);
    camera.setPosition(0, 5, 20);      // Position the camera
    camera.lookAt(ofVec3f(0, 0, 0));   // Look at the center of the scene

    // Initialize physics integrator and objects
    physicsIntegrator = PhysicsIntegrator();

    // Create a box and initialize its position, velocity, and angular velocity
    box = CorpsRigide();
    box.setPosition(Vector(0, 5, 0));           // Initial position
    box.setMass(1.0f);                          // Set the mass of the box
    box.setInertiaTensor(Matrix3::identity());  // Initial inertia tensor

    // Apply gravity as a constant force
    physicsIntegrator.addForce(&box, gravity * box.getMass());
}

// Update the scene with physics calculations
void ofApp::update() {
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
    // Update physics simulation
    physicsIntegrator.update(box, ofGetLastFrameTime());

    // Check if the box goes out of bounds and reset it if necessary
    if (box.getPosition().y < -10) {
        resetBox();
    }
}

void ofApp::draw() {
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
    titleFont.drawString("SIMULATEUR DE TIRS BALISTIQUES 3D", ofGetWidth() / 2 - titleFont.stringWidth("SIMULATEUR DE TIRS BALISTIQUES 3D") / 2, ofGetHeight() / 2 - 50);

    startButton->Draw();

    ofSetColor(255);
    drawNames();
}

void ofApp::drawNames() {
    ofSetColor(255, 255, 255);
    m_creditFont.drawString("Hugo Brisset", 0, ofGetHeight() - 100);
    m_creditFont.drawString("Alexandre Belisle-Huard", 0, ofGetHeight() - 70);
    m_creditFont.drawString("Albin Horlaville", 0, ofGetHeight() - 40);
    m_creditFont.drawString("Alan Fresco", 0, ofGetHeight() - 10);
}

// Draw the scene, including the box
void ofApp::drawGame() {
    returnButton->Draw();
    camera.begin();

    ofPushMatrix();
    ofTranslate(box.getPosition().toOfVec3f());
    ofMultMatrix(box.getOrientation().toOfMatrix4());  // Apply the box's rotation

    // Draw a small sphere to mark the center of mass
    ofSetColor(ofColor::black);
    ofDrawSphere(0, 0, 0, 0.2); // Small sphere at center of mass

    // Define the vertices of the cube
    glm::vec3 vertices[8] = {
        glm::vec3(-1, -1, -1), glm::vec3(1, -1, -1), glm::vec3(1, 1, -1), glm::vec3(-1, 1, -1),
        glm::vec3(-1, -1, 1), glm::vec3(1, -1, 1), glm::vec3(1, 1, 1), glm::vec3(-1, 1, 1)
    };

    // Define the faces of the cube
    int faces[6][4] = {
        {0, 1, 2, 3}, {1, 5, 6, 2}, {5, 4, 7, 6}, {4, 0, 3, 7}, {0, 1, 5, 4}, {3, 2, 6, 7}
    };

    // Define colors for each face
    ofColor colors[6] = {
        ofColor::red, ofColor::green, ofColor::blue,
        ofColor::yellow, ofColor::cyan, ofColor::magenta
    };

    // Draw each face with a different color
    for (int i = 0; i < 6; ++i) {
        ofSetColor(colors[i]);
        ofFill();
        ofBeginShape();
        for (int j = 0; j < 4; ++j) {
            ofVertex(vertices[faces[i][j]]);
        }
        ofEndShape(true);
    }

    ofPopMatrix();

    camera.end();

    // Draw the launch force value on the screen
    ofSetColor(ofColor::white);
    std::string launchForceText = "Launch Force: " + std::to_string(launchForce);
    launchForceFont.drawString(launchForceText, 20, 20);
}

// Reset the box position and velocity when it goes out of bounds
void ofApp::resetBox() {
    box.setPosition(Vector(0, 5, 0));         // Reset position
    box.setVelocity(Vector(0, 0, 0));         // Reset velocity
    box.setAngularVelocity(Vector(0, 0, 0));  // Reset angular velocity
    // Reset launch force
	launchForce = 0.0f;
}

// Reset the camera position and orientation
void ofApp::resetCamera() {
    camera.setPosition(0, 5, 20);      // Reset position
    camera.lookAt(ofVec3f(0, 0, 0));   // Reset orientation
}

void ofApp::mouseMoved(int x, int y) {
    if (currentState == MENU) {
        startButton->isHover(x, y);
    }
    else if (currentState == GAME) {
        returnButton->isHover(x, y);
    }
}

// Apply a force at an offset from the center of mass when the user clicks
void ofApp::mousePressed(int x, int y, int button) {
    if (currentState == MENU && startButton->isHover(x, y)) {
        currentState = GAME;
    }
    else if (currentState == GAME) {
        if (returnButton->isHover(x, y)) {
            currentState = MENU;
			resetBox();
			resetCamera();
        }
        else {
            // Calculate the direction of launch from the mouse position
            glm::vec3 mousePosWorld = camera.screenToWorld(ofVec3f(x, y, 0));
            Vector direction = (Vector::fromGlmVec3(mousePosWorld) - box.getPosition()).normalize();
            Vector force = direction * launchForce;

            // Apply the force at an offset from the center of mass
            Vector offset(0.5f, 0.5f, 0); // Example offset from center
            box.applyForceAtPoint(force, box.getPosition() + offset);

            // Add a torque based on the offset to induce rotation
            Vector torque = offset.cross(force) * torqueFactor;
            box.applyTorque(torque);
        }
    }
}

// Handle key presses for resetting or adjusting launch force
void ofApp::keyPressed(int key) {
    if (currentState == MENU) {
		// If Enter is pressed, start the game
		if (key == OF_KEY_RETURN) {
			currentState = GAME;
		}
	}
    else if (currentState == GAME) {
        switch (key) {
        case 'r':
            cout << "Resetting box position and velocity." << endl;
            resetBox();
            resetCamera();
            break;
        case OF_KEY_UP:
            cout << "Up key pressed" << endl;
            launchForce += 5.0f;
            break;
        case OF_KEY_DOWN:
            cout << "Down key pressed" << endl;
            launchForce -= 5.0f;
            if (launchForce < 0) launchForce = 0;
            break;
        }
    }
}
