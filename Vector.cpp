#include "Vector.h"

// Constructeurs
Vector::Vector() : x(0), y(0), z(0) {}

Vector::Vector(double x, double y, double z) : x(x), y(y), z(z) {}

// Methodes
double Vector::getNorme() const
{
    return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

double Vector::getNormeAuCarre() const
{
    return pow(x, 2) + pow(y, 2) + pow(z, 2);
}

void Vector::normalize()
{
    double norme = getNorme();
    if (norme != 0) {
        x /= norme;
        y /= norme;
        z /= norme;
    }
}

void Vector::print(std::ostream& flux) const
{
    flux << "(" << x << ", " << y << ", " << z << ")";
}

void Vector::afficher() const
{
    std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
}

glm::vec3 Vector::getGlmVec() const
{
    return glm::vec3(x, y, z);
}

// Operateurs
Vector& Vector::operator+=(const Vector& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vector& Vector::operator-=(const Vector& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

Vector& Vector::operator*=(double num)
{
    x *= num;
    y *= num;
    z *= num;
    return *this;
}

Vector& Vector::operator/=(double num)
{
    if (num != 0) {
        x /= num;
        y /= num;
        z /= num;
    }
    return *this;
}

// Operateurs externes
Vector operator+(const Vector& v1, const Vector& v2)
{
    Vector resultat(v1);
    resultat += v2;
    return resultat;
}

Vector operator-(const Vector& v1, const Vector& v2)
{
    Vector resultat(v1);
    resultat -= v2;
    return resultat;
}

Vector& Vector::operator*=(Vector const& v) {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
}

Vector operator*(Vector const& v1, Vector const& v2) {
    Vector vec(v1);
    vec *= v2;
    return vec;
}

Vector operator*(const Vector& vec, double num)
{
    Vector copie(vec);
    copie *= num;
    return copie;
}

Vector operator/(const Vector& vec, double num)
{
    Vector copie(vec);
    copie /= num;
    return copie;
}

bool operator==(const Vector& v1, const Vector& v2)
{
    return (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z);
}

std::ostream& operator<<(std::ostream& flux, const Vector& v)
{
    v.print(flux);
    return flux;
}

// Fonctions amies
double produitScalaire(const Vector& v1, const Vector& v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector produitVectoriel(const Vector& v1, const Vector& v2)
{
    return Vector(
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
    );
}
