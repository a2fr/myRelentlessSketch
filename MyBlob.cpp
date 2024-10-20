#include "MyBlob.h"


MyBlob::MyBlob()
{
    // Cr�ation des particules
    for (int i = 0; i < 3; ++i) {
        Particle* p = new Particle(Vector(ofRandom(200,400), ofRandom(20, 200), 0));
        particles.push_back(p);
    }
}

// Met � jour le blob (position, forces appliqu�es, collisions)
void MyBlob::update(float deltaTime) {
}

// Dessine le blob � l'�cran
void MyBlob::draw() {
    // Dessiner chaque particule
    for (Particle* p : particles) {
        p->draw();
    }
}

// Retourne le nombre de particules attach�es au blob
int MyBlob::getParticleCount() const {
    return particles.size();
}

void MyBlob::addParticle()
{
    Particle* p = new Particle(Vector(ofRandom(200, 400), ofRandom(20, 200), 0));
    particles.push_back(p);
}
