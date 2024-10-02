#ifndef Particule_h
#define Particule_h

#include "Vector.h"
#include "ofMain.h"

class Particle
{
private:
    float m_width;
    Vector m_position;
    Vector m_velocity;
    Vector m_acceleration;
    float m_inverseMasse;
    ofColor m_color;
    Vector m_accumForce;


//  float restitution; // Coefficient de restitution (pour les collisions)

public:
    Particle(Vector pos = Vector(0, 0, 0), float w = 10, float Im = 1.0f, ofColor color = ofColor::blue, Vector velocity = Vector(), Vector a = Vector()) :
        m_width(w), m_position(pos), m_velocity(velocity), m_acceleration(a), m_inverseMasse(Im), m_color(color) {};
    ~Particle() {}

/* ----------------------------- Getteurs & Setteurs ----------------------------- */
    void setVelocity(Vector v) { m_velocity = v; };
    Vector getVelocity() { return m_velocity; };

    Vector& getPosition() { return m_position; };
    void setPosition(Vector v) { m_position = v; };

    void setColor(ofColor c) { m_color = c; };

    float getInverseMasse() const { return m_inverseMasse; };
    void setInverseMasse(float inverseMasse) { m_inverseMasse = inverseMasse; };

/* ----------------------------- ----------------------------- ----------------------------- */
    void update(float deltaTime); // Modifie pour inclure le temps ecoule
    void draw() const;
    void addForce(const Vector& force);

    void clearAccum();

};

#endif // Particule_h