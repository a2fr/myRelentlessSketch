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

// Retourne le nombre de particules attach�es au blob
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
    if (rand() < (0.8 * RAND_MAX)) {
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
        int halfSize = particles.size() / 2;
        // Cr�er un nouveau blob
        MyBlob* newBlob = new MyBlob();
        for (int i = particles.size() -1 ; i >= halfSize; i--) {
            std::cout << "add" << std::endl;
            newBlob->addParticle(particles[i]); // Ajouter au nouveau blob
            particles.pop_back();
        }
        for (Particle* p : newBlob->particles) {
            // Mettre � jour l'�tat isPlayer de chaque particule
            p->setIsPlayer(false);
            p->setColor(ofColor::blue);
            p->setRefBlob(newBlob);
        }
       
        float separationDistance = 100.0f; // Distance pour s�parer les blobs
        for (Particle* p : newBlob->particles) {
            Vector newPosition = p->getPosition() + Vector(separationDistance, 0, 0); // D�place vers la droite
            p->setPosition(newPosition); // Met � jour la position
        }

        // Optionnel : d�placer �galement les particules restantes de l'ancien blob
        for (Particle* p : particles) {
            Vector newPosition = p->getPosition() + Vector(-separationDistance, 0, 0); // D�place vers la gauche
            p->setPosition(newPosition); // Met � jour la position
        }

        // Appliquer une force de s�paration ou une vitesse initiale aux particules
        Vector separationForce(100, 0, 0); // Exemple de force de s�paration vers la droite
        for (Particle* p : newBlob->particles) {
            p->setVelocity(p->getVelocity() + separationForce); // Appliquer la force de s�paration
        }

        // Optionnel : appliquer une force de s�paration � l'ancien blob �galement
        Vector reverseSeparationForce(-100, 0, 0); // Force de s�paration oppos�e
        for (Particle* p : particles) {
            p->setVelocity(p->getVelocity() + reverseSeparationForce); // Appliquer la force de s�paration
        }

        // Garder la premi�re moiti� dans le blob actuel
        return newBlob; // Retourner le nouveau blob
}

void MyBlob::collapse(MyBlob& otherBlob)
{
    // R�cup�rer le nombre total de particules dans l'autre blob
    int otherCount = otherBlob.getParticleCount();

    // Ajouter toutes les particules de l'autre blob au blob actuel
    for (int i = 0; i < otherCount; ++i) {
        Particle* p = otherBlob.particles[i]; // R�cup�rer la particule de l'autre blob
        particles.push_back(p); // Ajouter la particule au blob actuel
        p->setRefBlob(this); // Mettre � jour la r�f�rence au blob actuel
    }
}



