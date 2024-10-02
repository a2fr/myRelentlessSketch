#include "ForceGenerator.h"

class ForceGenerator {
public:
    virtual void applyForce(Particle* particle, float duration) = 0;
};

class ForceRegistry {
public:
    struct ForceRegistration {  // Move this to 'public'
        Particle* particle;
        ForceGenerator* generator;
    };

    typedef std::vector<ForceRegistration> Registry;
    Registry registry;

    void add(Particle* particle, ForceGenerator* generator) {
        ForceRegistration registration;
        registration.particle = particle;
        registration.generator = generator;
        registry.push_back(registration);
    }

    void remove(Particle* particle, ForceGenerator* generator) {
        Registry::iterator i = registry.begin();
        for (; i != registry.end(); i++) {
            if (i->particle == particle && i->generator == generator) {
                registry.erase(i);
                return;
            }
        }
    }

    void clear() {
        registry.clear();
    }

    void updateForces(float duration) {
        Registry::iterator i = registry.begin();
        for (; i != registry.end(); i++) {
            i->generator->applyForce(i->particle, duration);
        }
    }
};
