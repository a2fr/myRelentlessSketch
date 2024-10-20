#include "Particle.h"

void Particle::update(float deltaTime)
{
    m_acceleration = m_accumForce * m_inverseMasse;

    m_velocity += m_acceleration * deltaTime;
    m_position += m_velocity * deltaTime;
}

void Particle::draw() const
{
    ofSetColor(m_color);
    ofFill();
    ofDrawSphere(m_position.getGlmVec(), m_width);
}

void Particle::addForce(const Vector& force) {
    m_accumForce += force;
}

void Particle::clearAccum()
{
    m_accumForce = Vector(0, 0, 0);
}

// Get the width of the particle
float Particle::getWidth() const
{
    return m_width;
}

// Get the acceleration of the particle
Vector Particle::getAcceleration() const
{
    return m_acceleration;
}
