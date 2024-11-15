#include "ofApp.h"
#include <windows.h>

// Settings for the shooting game
float torqueFactor = 0.1f;

// Camera
bool isFocused = true;
float moveSpeed = 0.5f;
float sensitivity = 0.1f; // Ajuste la sensibilité de la rotation
glm::vec2 centerOfTheScreen;
bool keys[6] = { false, false, false, false, false, false }; // W, A, S, D, R, F

// Setup the application window and scene
void ofApp::setup() {
    titleFont.load("goodtimesrg.otf", 55);
    m_creditFont.load("goodtimesrg.otf", 20);
    launchForceFont.load("goodtimesrg.otf", 20);
    controlsFont.load("goodtimesrg.otf", 10);

    currentState = MENU;

    // Define the start button rectangle
    startButton = new Button("START", ofRectangle(ofGetWidth() / 2 - 100, ofGetHeight() / 2 + 50, 200, 50), false);
    returnButton = new Button("RETURN", ofRectangle(ofGetWidth() - 120, 10, 100, 25), false);

    // Configure the camera
    camera.setPosition(0, 5, 20);      // Position the camera
    camera.lookAt(ofVec3f(0, 0, 0));   // Look at the center of the scene
    camera.setNearClip(1.0f);
    centerOfTheScreen = glm::vec2(ofGetWidth() / 2, ofGetHeight() / 2);
    SetCursorPos(centerOfTheScreen.x, centerOfTheScreen.y); // Centre la souris au début

    // Initialize physics integrator and objects
    physicsIntegrator = PhysicsIntegrator();

    // Create a box and initialize its position, velocity, and angular velocity
    box = CorpsRigide();
    box.setPosition(Vector(0, 5, 0));           // Initial position
    box.setMass(0.1f);                          // Set the mass of the box
    box.setCenterMass(Vector(1, 1, 1));
    box.setInertiaTensor(Matrix3::identite());  // Initial inertia tensor

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
    glm::vec3 newPos = (camera.getPosition() + moveDirection);
    if (newPos.y < 1.85)
        newPos.y = 1.85; // Hauteur de mes yeux
    camera.setPosition(newPos);

    glm::vec2 mousePos;
    if (isFocused) {
        mousePos = glm::vec2(ofGetMouseX(), ofGetMouseY());
    }
    else {
        mousePos = glm::vec2(centerOfTheScreen.x, centerOfTheScreen.y);
    }

    // Calculer la différence (déplacement) de la souris
    glm::vec2 delta = mousePos - centerOfTheScreen;

    // Appliquer la sensibilité et mettre à jour les angles de rotation
    float yaw = -delta.x * sensitivity;
    float pitch = -delta.y * sensitivity;

    // Limiter l'angle de pitch pour éviter les retournements
    pitch = ofClamp(pitch, -89.0f, 89.0f);

    // Appliquer les rotations de la caméra
    camera.setOrientation(glm::quat(glm::vec3(glm::radians(pitch), glm::radians(yaw), 0.0f)));

    // Recentrer la souris au milieu de l'écran
    if (isFocused)
        SetCursorPos(centerOfTheScreen.x, centerOfTheScreen.y);

    // Update physics simulation
    physicsIntegrator.update(box, ofGetLastFrameTime());

    // Check if the box goes out of bounds and reset it if necessary
    if (box.getPosition().y < 0) {
        box.setPosition(Vector(box.getPosition().x, 0, box.getPosition().z));
        box.setAngularVelocity(Vector(0, 0, 0));
        box.setVelocity(Vector(0, 0, 0));
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
    ofSetColor(255);
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
    ofSetColor(50, 150, 50); // Couleur verte pour le sol
    float width = 500.0f;  // Largeur du sol
    float depth = 500.0f;  // Profondeur du sol
    float yPos = -10.0f;   // Position en hauteur (y)

    ofDrawBox(glm::vec3(0, yPos, 0), 500, 1, 500);
    ofDrawGrid(1, 1000, false, false, true, false);

    // Cube
    ofPushMatrix();
    ofTranslate(box.getPosition().getGlmVec());
    ofMultMatrix(box.getOrientation().toMatrix4().toOfMatrix4x4());  // Apply the box's rotation

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

    ofSetColor(255, 0, 0);
    for (auto point : box.trace) {
        ofDrawSphere(point.getGlmVec(), 0.3);
    }

    camera.end();

    // CrossHair
    ofSetColor(255, 0, 0);
    glm::uvec2 center(ofGetWidth() / 2, ofGetHeight() / 2);
    int sizeBranch = 10;
    ofDrawLine(center + glm::vec2(-sizeBranch, 0), center + glm::vec2(sizeBranch, 0));
    ofDrawLine(center + glm::vec2(0, -sizeBranch), center + glm::vec2(0, sizeBranch));

    // Draw the launch force value on the screen
    ofSetColor(ofColor::white);
    std::string text;
    text = "Launch Force: " + std::to_string(launchForce);
    launchForceFont.drawString(text, 20, 20);
    text = "ENTRER - reset the cube";
    controlsFont.drawString(text, 20, 50);
    text = "W - move forward";
    controlsFont.drawString(text, 20, 65);
    text = "S - move backward";
    controlsFont.drawString(text, 20, 80);
    text = "A - move to the left";
    controlsFont.drawString(text, 20, 95);
    text = "D - move to the right";
    controlsFont.drawString(text, 20, 110);
    text = "R - move up";
    controlsFont.drawString(text, 20, 125);
    text = "F - move down";
    controlsFont.drawString(text, 20, 140);
    text = "Q - focus / unfocus";
    controlsFont.drawString(text, 20, 155);
}

// Reset the box position and velocity when it goes out of bounds
void ofApp::resetBox() {
    box.setPosition(Vector(0, 5, 0));         // Reset position
    box.setVelocity(Vector(0, 0, 0));         // Reset velocity
    box.setAngularVelocity(Vector(0, 0, 0));  // Reset angular velocity
    box.orientation = Quaternion(1, 0, 0, 0);
    box.isGravityActivated = false;
    box.trace = vector<Vector>();
    // Reset launch force
    launchForce = 100.0f;
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
        isFocused = true;
    }
    else if (currentState == GAME) {
        if (returnButton->isHover(x, y)) {
            currentState = MENU;
            resetBox();
            resetCamera();
            ofShowCursor();
        }
        else {
            // Calculate the direction of launch from the mouse position
            Vector direction = (box.getPosition() - Vector(camera.getPosition())).normalize();
            Vector force = direction * launchForce;

            // Apply the force at an offset from the center of mass
            Vector offset(0, 0, 0); // Example offset from center
            box.applyForceAtPoint(force, box.getPosition() + offset - direction);

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
        if (key == 'w') keys[0] = true;
        if (key == 'a') keys[1] = true;
        if (key == 's') keys[2] = true;
        if (key == 'd') keys[3] = true;
        if (key == 'r') keys[4] = true;
        if (key == 'f') keys[5] = true;
        switch (key) {
        case 'q':
            if (isFocused) {
                isFocused = false;
                ofShowCursor();
            }
            else {
                isFocused = true;
                ofHideCursor();
            }
            break;
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
    if (key == 'w') keys[0] = false;
    if (key == 'a') keys[1] = false;
    if (key == 's') keys[2] = false;
    if (key == 'd') keys[3] = false;
    if (key == 'r') keys[4] = false;
    if (key == 'f') keys[5] = false;
}
