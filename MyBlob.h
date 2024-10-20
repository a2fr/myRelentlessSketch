#ifndef MyBlob_h
#define MyBlob_h

#include "Particle.h"
#include "Player.h"
#include <vector>

class MyBlob {
public:
    // Constructeur et destructeur
    MyBlob();
    MyBlob(Player* player);

    // M�thodes principales
    void update(float deltaTime);

    void draw();

    // M�thode pour acc�der au nombre de particules attach�es au Blob
    int getParticleCount() const;
    void addParticle(Particle* p);
    void addParticle();

    std::vector<Particle*> particles;  // Liste des particules constituant le blob
private:
      

};

#endif //MyBlob.h
