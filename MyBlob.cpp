#include "MyBlob.h"


MyBlob::MyBlob()
{
    // Création des particules
    for (int i = 0; i < 5; ++i) {
        Particle* p = new Particle(Vector(ofRandom(200,400), ofRandom(20, 200), 0), 20);
        particles.push_back(p);
    }
}

MyBlob::MyBlob(Player* player)
{
    particles.push_back(player);
    for (int i = 0; i < 5; ++i) {
        Particle* p = new Particle(Vector(ofRandom(200, 400), ofRandom(20, 200), 0), 20);
        particles.push_back(p);
    }
}

void MyBlob::draw()
{
    particles[0]->draw();
    // Draw each particle
    for (int i = 1; i < particles.size()-1; i++) {
        particles[i]->draw();
        ofDrawLine(particles[i]->getPosition().getGlmVec(), particles[0]->getPosition().getGlmVec());
        ofDrawLine(particles[i]->getPosition().getGlmVec(), particles[i+1]->getPosition().getGlmVec());
    }

    particles[particles.size()-1]->draw();
    ofDrawLine(particles[particles.size()-1]->getPosition().getGlmVec(), particles[0]->getPosition().getGlmVec());
    ofDrawLine(particles[particles.size()-1]->getPosition().getGlmVec(), particles[1]->getPosition().getGlmVec());

}

// Retourne le nombre de particules attachées au blob
int MyBlob::getParticleCount() const {
    return particles.size();
}

void MyBlob::addParticle(Particle *p)
{
    particles.push_back(p);
}

void MyBlob::addParticle()
{
    Particle* p = new Particle(particles[0]->getPosition(), 20);
    particles.push_back(p);
}
