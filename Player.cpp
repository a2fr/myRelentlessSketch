#include "Player.h"

Player::Player(Vector pos, float w, float Im, ofColor color, Vector velocity, Vector a)
    : Particle(pos, w, Im, color, velocity, a) {}

void Player::handleInput() {
    if (ofGetKeyPressed(OF_KEY_LEFT)) {
        setVelocity(getVelocity() + Vector(-1, 0, 0));
    }
    if (ofGetKeyPressed(OF_KEY_RIGHT)) {
        setVelocity(getVelocity() + Vector(1, 0, 0));
    }
    if (ofGetKeyPressed(OF_KEY_UP)) {
        setVelocity(getVelocity() + Vector(0, -1, 0));
    }
    if (ofGetKeyPressed(OF_KEY_DOWN)) {
        setVelocity(getVelocity() + Vector(0, 1, 0));
    }
}
