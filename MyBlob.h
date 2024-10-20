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

    // Méthodes principales
    void update(float deltaTime);

    void draw();

    // Méthode pour accéder au nombre de particules attachées au Blob
    int getParticleCount() const;
    void addParticle(Particle* p);
    void addParticle();

    std::vector<Particle*> particles;  // Liste des particules constituant le blob
private:
      

};

#endif //MyBlob.h
