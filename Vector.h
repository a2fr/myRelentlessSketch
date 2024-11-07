// Vector.h
#ifndef VECTOR_H
#define VECTOR_H

#include "ofVec3f.h" // Include the OpenFrameworks vector header
#include <glm/glm.hpp> // Include the GLM vector header

class Vector {
public:
    float x, y, z;

    // Constructors
    Vector();
    Vector(float x, float y, float z);

    // Operators
    Vector operator+(const Vector& v) const;
    Vector operator-(const Vector& v) const;
    Vector operator*(float scalar) const;
    Vector operator/(float scalar) const;
    Vector& operator+=(const Vector& v);
    Vector& operator-=(const Vector& v);
    Vector& operator*=(float scalar);
    Vector& operator/=(float scalar);
    bool operator==(const Vector& v) const;
    bool operator!=(const Vector& v) const;

    // Methods
    float length() const;
    Vector normalize() const;
    Vector cross(const Vector& v) const;
    static float dot(const Vector& a, const Vector& b);

    // Conversion to ofVec3f
    ofVec3f toOfVec3f() const;

    // Conversion to glm::vec3
    glm::vec3 toGlmVec3() const;

    // Conversion from glm::vec3
    static Vector fromGlmVec3(const glm::vec3& v);
};

#endif // VECTOR_H
