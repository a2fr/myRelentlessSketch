#ifndef Vector_h
#define Vector_h

#include <iostream>
#include "glm/vec3.hpp"
#include <math.h>

class Vector
{
public:
    double x;
    double y;
    double z;

public:
    // Constructeurs
    Vector();
    Vector(double x, double y, double z);
    Vector(const glm::vec3& v);

    float getX() const { return x; };
    float getY() const { return y; };
    float getZ() const { return z; };
    void setY(float y) { this->y = y; };

    // Methodes
    double getNorme() const;
    double getNormeAuCarre() const;
    Vector normalize() const;

    void print(std::ostream& flux) const;
    void afficher() const;
    glm::vec3 getGlmVec() const;

    // Operateurs
    Vector& operator+=(const Vector& v);
    Vector& operator-=(const Vector& v);
    Vector& operator*=(Vector const& v);

    Vector& operator*=(double num);
    Vector& operator/=(double num);

    // Fonctions amies
    friend double produitScalaire(const Vector& v1, const Vector& v2);
    friend Vector produitVectoriel(const Vector& v1, const Vector& v2);
};

// Operateurs externes
Vector operator+(const Vector& v1, const Vector& v2);
Vector operator-(const Vector& v1, const Vector& v2);
Vector operator*(Vector const& v1, Vector const& v2);
Vector operator*(const Vector& vec, double num);
Vector operator/(const Vector& vec, double num);
Vector operator-(const Vector& vec);
bool operator==(const Vector& v1, const Vector& v2);
std::ostream& operator<<(std::ostream& flux, const Vector& v);

#endif // Vector_h