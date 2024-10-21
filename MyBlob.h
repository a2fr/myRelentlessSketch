#ifndef MyBlob_h
#define MyBlob_h

#include "Particle.h"
#include <cstdlib> 
#include <vector>

class MyBlob {
public:
    // Constructeur et destructeur
    MyBlob();

    void setUpMyBlob();
    void draw();

    // M�thode pour acc�der au nombre de particules attach�es au Blob
    int getParticleCount() const;
    void addParticle(Particle* p);
    void addParticle();

    MyBlob* split();
   
    std::vector<Particle*> particles;  // Liste des particules constituant le blob
private:
      

};

#endif //MyBlob.h
