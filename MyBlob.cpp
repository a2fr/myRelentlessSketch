#include "MyBlob.h"


MyBlob::MyBlob()
{
    // Création des particules
    for (int i = 0; i < 3; ++i) {
        Particle* p = new Particle(Vector(ofRandom(200,400), ofRandom(20, 200), 0));
        particles.push_back(p);
    }
}

// Met à jour le blob (position, forces appliquées, collisions)
void MyBlob::update(float deltaTime) {
}

// Dessine le blob à l'écran
void MyBlob::draw() {
    // Dessiner chaque particule
    for (Particle* p : particles) {
        p->draw();
    }
}

// Retourne le nombre de particules attachées au blob
int MyBlob::getParticleCount() const {
    return particles.size();
}

void MyBlob::addParticle()
{
    Particle* p = new Particle(Vector(ofRandom(200, 400), ofRandom(20, 200), 0));
    particles.push_back(p);
}
