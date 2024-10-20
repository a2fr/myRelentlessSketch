#ifndef MyBlob_h
#define MyBlob_h

#include "Particle.h"
#include <vector>

class MyBlob {
public:
    // Constructeur et destructeur
    MyBlob();

    // Méthodes principales
    void update(float deltaTime);      // Met à jour la position des particules et les forces
    void draw();                       // Dessine le blob à l'écran

    // Méthode pour accéder au nombre de particules attachées au Blob
    int getParticleCount() const;
    void addParticle();

private:
    std::vector<Particle*> particles;  // Liste des particules constituant le blob

};


#endif //MyBlob.h
