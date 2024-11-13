#ifndef Particule_h
#define Particule_h

#include "Vector.h"
#include "ofMain.h"

class MyBlob;

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
    bool IsPlayer;

    MyBlob* m_blob;
    

public:
    Particle(Vector pos = Vector(0, 0, 0), float w = 10, float Im = 1.0f, ofColor color = ofColor::blue, bool isPlayer = false, Vector velocity = Vector(), Vector a = Vector()) :
        m_width(w), m_position(pos), m_velocity(velocity), m_acceleration(a), m_inverseMasse(Im), m_color(color), IsPlayer(isPlayer) {};
    ~Particle() {}

    void setRefBlob(MyBlob* blob) { m_blob = blob; };
    MyBlob* getRefBlob() { return m_blob; };

    void setVelocity(Vector v) { m_velocity = v; };
    Vector getVelocity() { return m_velocity; };

    void setIsPlayer(bool isplayer) { IsPlayer = isplayer;  };

    const Vector& getPosition() const { return m_position; };
    void setPosition(Vector v) { m_position = v; };

    void setColor(ofColor c) { m_color = c; };

    float getInverseMasse() const { return m_inverseMasse; };
    void setInverseMasse(float inverseMasse) { m_inverseMasse = inverseMasse; };

    Vector getAcceleration() const; // Declare the getAcceleration function

    void update(float deltaTime);
    void draw() const;
    void addForce(const Vector& force);

    void clearAccum();

    Vector getForce() { return m_accumForce; };

    float getWidth() const;

    void handleInput();
};

#endif // Particule_h
