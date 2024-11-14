#include "ofApp.h"
#include <windows.h>

// Settings for the shooting game
float launchForce = 20.0f;
Vector launchPosition(0, 0, 0);
Vector gravity(0, -9.81f, 0);
float torqueFactor = 0.1f;

// Camera
float moveSpeed = 0.5f;
float sensitivity = 0.1f; // Ajuste la sensibilité de la rotation
float pitch = 0.0f, yaw = 0.0f;
glm::vec2 lastMousePos;
bool keys[6] = { false, false, false, false, false, false }; // Z, Q, S, D, R, F

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
    camera.setNearClip(0.01f);
    lastMousePos = glm::vec2(ofGetWidth() / 2, ofGetHeight() / 2);
    SetCursorPos(lastMousePos.x, lastMousePos.y); // Centre la souris au début

    // Initialize physics integrator and objects
    physicsIntegrator = PhysicsIntegrator();

    // Create a box and initialize its position, velocity, and angular velocity
    box = CorpsRigide();
    box.setPosition(Vector(0, 5, 0));           // Initial position
    box.setMass(1.0f);                          // Set the mass of the box
    box.setInertiaTensor(Matrix3::identite());  // Initial inertia tensor

    // Apply gravity as a constant force
    physicsIntegrator.addForce(&box, gravity * box.getMass());

    skybox.setup();
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
    // Récupérer la direction de la caméra
    glm::vec3 forward = camera.getLookAtDir(); // Direction vers l'avant
    glm::vec3 right = glm::cross(forward, glm::vec3(0, 1, 0)); // Direction à droite
    glm::vec3 up(0, 1, 0); // Vers le haut

    glm::vec3 moveDirection = glm::vec3(0.0f); // Reset du vecteur de direction

    // Ajuster les directions en fonction des touches
    if (keys[0]) moveDirection += forward * moveSpeed; // Z - Avancer
    if (keys[2]) moveDirection -= forward * moveSpeed; // S - Reculer
    if (keys[1]) moveDirection -= right * moveSpeed;   // Q - Gauche
    if (keys[3]) moveDirection += right * moveSpeed;   // D - Droite
    if (keys[4]) moveDirection += up * moveSpeed;      // R - Monter
    if (keys[5]) moveDirection -= up * moveSpeed;      // F - Descendre

    // Appliquer le déplacement à la position de la caméra
    camera.setPosition(camera.getPosition() + moveDirection);

    glm::vec2 mousePos(ofGetMouseX(), ofGetMouseY());

    // Calculer la différence (déplacement) de la souris
    glm::vec2 delta = mousePos - lastMousePos;

    // Appliquer la sensibilité et mettre à jour les angles de rotation
    yaw = -delta.x * sensitivity;
    pitch = -delta.y * sensitivity;

    // Limiter l'angle de pitch pour éviter les retournements
    pitch = ofClamp(pitch, -89.0f, 89.0f);

    // Appliquer les rotations de la caméra
    camera.setOrientation(glm::quat(glm::vec3(glm::radians(pitch), glm::radians(yaw), 0.0f)));

    SetCursorPos(ofGetWidth() / 2, ofGetHeight() / 2);
    lastMousePos = glm::vec2(ofGetWidth() / 2, ofGetHeight() / 2);

    // Update physics simulation
    physicsIntegrator.update(box, ofGetLastFrameTime());

    // Check if the box goes out of bounds and reset it if necessary
    //if (box.getPosition().y < -10) {
    //    resetBox();
    //}
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
    ofBackground(0);  // Fond noir
    skybox.draw();

    returnButton->Draw();
    camera.begin();

    // Dessiner le sol
    ofSetColor(100, 200, 100); // Couleur verte pour le sol
    float width = 500.0f;  // Largeur du sol
    float depth = 500.0f;  // Profondeur du sol
    float yPos = -10.0f;   // Position en hauteur (y)

    ofDrawBox(glm::vec3(0, yPos, 0), 500, 1, 500);

    // Cube
    ofPushMatrix();
    ofTranslate(box.getPosition().getGlmVec());
    ofMultMatrix(box.getOrientation().toMatrix4().toOfMatrix4x4());  // Apply the box's rotation

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
        ofHideCursor(); // Cache le curseur de la souris
        SetCursorPos(ofGetWidth() / 2, ofGetHeight() / 2);
    }
    else if (currentState == GAME) {
        if (returnButton->isHover(x, y)) {
            currentState = MENU;
            resetBox();
            resetCamera();
            ofShowCursor();
        }
        else {
            Vector mousePosWorld = Vector(x,y,0);
            // Calculate the direction of launch from the mouse position
            //glm::vec3 mousePosWorld = camera.screenToWorld(ofVec3f(x, y, 0));
            Vector direction = (mousePosWorld - box.getPosition()).normalize();
            Vector force = direction * launchForce;

            // Apply the force at an offset from the center of mass
            Vector offset(0.5f, 0.5f, 0); // Example offset from center
            box.applyForceAtPoint(force, box.getPosition() + offset);

            // Add a torque based on the offset to induce rotation
            Vector torque = produitVectoriel(offset, force) * torqueFactor;
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
        if (key == 'z') keys[0] = true;
        if (key == 'q') keys[1] = true;
        if (key == 's') keys[2] = true;
        if (key == 'd') keys[3] = true;
        if (key == 'r') keys[4] = true;
        if (key == 'f') keys[5] = true;
        switch (key) {
        case OF_KEY_RETURN:
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

void ofApp::keyReleased(int key) {
    if (key == 'z') keys[0] = false;
    if (key == 'q') keys[1] = false;
    if (key == 's') keys[2] = false;
    if (key == 'd') keys[3] = false;
    if (key == 'r') keys[4] = false;
    if (key == 'f') keys[5] = false;
}
