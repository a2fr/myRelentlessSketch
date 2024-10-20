#ifndef MyBlob_h
#define MyBlob_h

#include "Particle.h"
#include <vector>

class MyBlob {
public:
    // Constructeur et destructeur
    MyBlob();

    // M�thodes principales
    void update(float deltaTime);      // Met � jour la position des particules et les forces
    void draw();                       // Dessine le blob � l'�cran

    // M�thode pour acc�der au nombre de particules attach�es au Blob
    int getParticleCount() const;
    void addParticle();

private:
    std::vector<Particle*> particles;  // Liste des particules constituant le blob

};


#endif //MyBlob.h
