#include "..\CorpsRigide.h"         // Your rigid body class
#include <windows.h>
#include "ofApp.h"

// Settings for the shooting game
float torqueFactor = 0.1f;

// Camera
bool isFocused = true;
float moveSpeed = 0.5f;
float sensitivity = 0.1f; // Ajuste la sensibilite de la rotation
glm::vec2 centerOfTheScreen;
bool keys[6] = { false, false, false, false, false, false }; // W, A, S, D, R, F

bool drawArrow = false;
Vector collisionPoint;
Vector direction;

// Object that the user see in game
CorpsRigide* currentObject;

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
    camera.setPosition(0, 1.85, 20);      // Position the camera
    camera.lookAt(ofVec3f(0, 0, 0));   // Look at the center of the scene
    camera.setNearClip(1.0f);
    centerOfTheScreen = glm::vec2(ofGetWidth() / 2, ofGetHeight() / 2);
    SetCursorPos(centerOfTheScreen.x, centerOfTheScreen.y); // Centre la souris au debut

    // LIGHTS
    ofSetSmoothLighting(true);
    pointLight.setDiffuseColor(ofColor(246, 228, 188));
    pointLight.setSpecularColor(ofColor(246, 228, 188));
    pointLight.setPosition(0, 50, 0);
    pointLight.setScale(1000);
    directionalLight.setDiffuseColor(ofColor(246, 228, 188));
    directionalLight.setSpecularColor(ofColor(246, 228, 188));
    directionalLight.setPosition(0, 50, 0);
    directionalLight.setOrientation(glm::vec3(45, 45, 45));

    // Initialize physics integrator and objects
    physicsIntegrator = PhysicsIntegrator();

    //skybox.setup();

    currentObject = &cube;
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
    // Recuperer la direction de la camera
    glm::vec3 forward = camera.getLookAtDir(); // Direction vers l'avant
    glm::vec3 right = glm::cross(forward, glm::vec3(0, 1, 0)); // Direction a droite
    glm::vec3 up(0, 1, 0); // Vers le haut

    glm::vec3 moveDirection = glm::vec3(0.0f); // Reset du vecteur de direction

    // Ajuster les directions en fonction des touches
    if (keys[0]) moveDirection += forward * moveSpeed; // Z - Avancer
    if (keys[2]) moveDirection -= forward * moveSpeed; // S - Reculer
    if (keys[1]) moveDirection -= right * moveSpeed;   // Q - Gauche
    if (keys[3]) moveDirection += right * moveSpeed;   // D - Droite
    if (keys[4]) moveDirection += up * moveSpeed;      // R - Monter
    if (keys[5]) moveDirection -= up * moveSpeed;      // F - Descendre

    // Appliquer le deplacement a la position de la cam�ra
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

    // Calculer la difference (d�placement) de la souris
    glm::vec2 delta = mousePos - centerOfTheScreen;

    // Appliquer la sensibilite et mettre a jour les angles de rotation
    float yaw = -delta.x * sensitivity;
    float pitch = -delta.y * sensitivity;

    // Limiter l'angle de pitch pour eviter les retournements
    pitch = ofClamp(pitch, -89.0f, 89.0f);

    // Appliquer les rotations de la cam�ra
    camera.setOrientation(glm::quat(glm::vec3(glm::radians(pitch), glm::radians(yaw), 0.0f)));

    // Recentrer la souris au milieu de l'�cran
    if (isFocused)
        SetCursorPos(centerOfTheScreen.x, centerOfTheScreen.y);

    // Update physics simulation
    physicsIntegrator.update(*currentObject, ofGetLastFrameTime());

    // Check if the box goes out of bounds and reset it if necessary
    if (currentObject->getPosition().y < 0) {
        currentObject->setPosition(Vector(currentObject->getPosition().x, 0, currentObject->getPosition().z));
        currentObject->setAngularVelocity(Vector(0, 0, 0));
        currentObject->setVelocity(Vector(0, 0, 0));
    }

    pointLight.setPosition(currentObject->getPosition().getGlmVec());
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
    ofBackground(100,100,200);  // Fond noir
    ofEnableDepthTest();
    pointLight.enable();
    directionalLight.enable();
    //skybox.draw();

    returnButton->Draw();
    camera.begin();

    // Dessiner le sol
    ofSetColor(50, 150, 50); // Couleur verte pour le sol
    float width = 500.0f;  // Largeur du sol
    float depth = 500.0f;  // Profondeur du sol
    float yPos = -10.0f;   // Position en hauteur (y)

    ofDrawBox(glm::vec3(0, yPos, 0), 500, 1, 500);
    ofDrawGrid(1, 1000, false, false, true, false);

    // Trace
    ofSetColor(0, 0, 200);
    for (auto const& point : currentObject->trace) {
        ofDrawSphere(point.getGlmVec(), 0.2);
    }

    // Arrow
    if (drawArrow) {
        ofSetColor(255);
        glm::vec3 end = collisionPoint.getGlmVec();
        glm::vec3 start = end - direction.getGlmVec() * launchForce / 50;
        ofDrawArrow(start, end, 0.5f);
    }

    // Draw the current object
    currentObject->draw();

    pointLight.disable();
    directionalLight.disable();
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
    text = "J - switch to Cube";
    controlsFont.drawString(text, 20, 170);
    text = "K - switch to Cylindre";
    controlsFont.drawString(text, 20, 185);
    text = "L - switch to PaveDroit";
    controlsFont.drawString(text, 20, 200);
}

// Reset the box position and velocity when it goes out of bounds
void ofApp::resetBox() {
    currentObject->setPosition(Vector(0, 5, 0));         // Reset position
    currentObject->setVelocity(Vector(0, 0, 0));         // Reset velocity
    currentObject->setAngularVelocity(Vector(0, 0, 0));  // Reset angular velocity
    currentObject->orientation = Quaternion(1, 0, 0, 0);
    currentObject->isGravityActivated = false;
    currentObject->trace = vector<Vector>();
    // Reset launch force
    launchForce = 100.0f;
    drawArrow = false;
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
            direction = (currentObject->getPosition() - Vector(camera.getPosition())).normalize();
            Vector force = direction * launchForce;

            collisionPoint = currentObject->getPosition() + direction;
            drawArrow = true;

            // Apply the force at an offset from the center of mass
            currentObject->applyForceAtPoint(force, collisionPoint);
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
            resetBox();
            resetCamera();
            break;
        case OF_KEY_UP:
            launchForce += 5.0f;
            break;
        case OF_KEY_DOWN:
            launchForce -= 5.0f;
            if (launchForce < 0) launchForce = 0;
            break;
        case 'j':
            currentObject = &cube;
            break;
        case 'k':
            currentObject = &cylindre;
            break;
        case 'l':
            currentObject = &paveDroit;
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
