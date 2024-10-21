#include "MyBlob.h"


MyBlob::MyBlob()
{
}

void MyBlob::setUpMyBlob()
{
    for (int i = 0; i < 3; ++i) {
        Particle* p = new Particle(Vector(ofRandom(200, 400), ofRandom(20, 200), 0), 20, 0.5f, ofColor::purple, true);
        p->setRefBlob(this);
        particles.push_back(p);
    }
}

void MyBlob::draw()
{

    // Draw each particle
    for (int i = 0; i < particles.size()-2; i++) {
        particles[i]->draw();
        ofDrawLine(particles[i]->getPosition().getGlmVec(), particles[i+1]->getPosition().getGlmVec());
        ofDrawLine(particles[i]->getPosition().getGlmVec(), particles[i+2]->getPosition().getGlmVec());
    }
    int beforelast = particles.size() - 1;
    int last = particles.size() - 2;
    particles[beforelast]->draw();
    ofDrawLine(particles[beforelast]->getPosition().getGlmVec(), particles[last]->getPosition().getGlmVec());
    ofDrawLine(particles[beforelast]->getPosition().getGlmVec(), particles[0]->getPosition().getGlmVec());
    particles[last]->draw();
    ofDrawLine(particles[last]->getPosition().getGlmVec(), particles[0]->getPosition().getGlmVec());
    ofDrawLine(particles[last]->getPosition().getGlmVec(), particles[1]->getPosition().getGlmVec());
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
    Particle* p;
    if (rand() < (0.5 * RAND_MAX)) {
        p = new Particle(particles[0]->getPosition(), 20, 0.25f, ofColor::purple, true);
    }
    else {
        p = new Particle(particles[0]->getPosition(), 20, 0.5f);
    }
    p->setRefBlob(this);
    particles.push_back(p);
}

MyBlob* MyBlob::split()
{
        // Vérifie s'il y a suffisamment de particules pour séparer
        if (particles.size() <= 2) {
            return nullptr; // Pas assez de particules pour faire une séparation
        }

        int halfSize = particles.size() / 2;
        // Créer un nouveau blob
        MyBlob* newBlob = new MyBlob();
        for (int i = particles.size() -1 ; i >= halfSize; i--) {
            std::cout << "add" << std::endl;
            newBlob->addParticle(particles[i]); // Ajouter au nouveau blob
            particles.pop_back();
        }
        for (Particle* p : newBlob->particles) {
            // Mettre à jour l'état isPlayer de chaque particule
            p->setIsPlayer(false);
            p->setColor(ofColor::blue);
            p->setRefBlob(newBlob);
        }
       
        // Garder la première moitié dans le blob actuel
        //particles.resize(halfSize); // Redimensionner pour garder uniquement la première moitié
        return newBlob; // Retourner le nouveau blob
}



