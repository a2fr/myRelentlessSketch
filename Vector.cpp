// Vector.cpp
#include "Vector.h"
#include <cmath> // For sqrt

// Constructors
Vector::Vector() : x(0), y(0), z(0) {}

Vector::Vector(float x, float y, float z) : x(x), y(y), z(z) {}

// Operators
Vector Vector::operator+(const Vector& v) const {
    return Vector(x + v.x, y + v.y, z + v.z);
}

Vector Vector::operator-(const Vector& v) const {
    return Vector(x - v.x, y - v.y, z - v.z);
}

Vector Vector::operator*(float scalar) const {
    return Vector(x * scalar, y * scalar, z * scalar);
}

Vector Vector::operator/(float scalar) const {
    return Vector(x / scalar, y / scalar, z / scalar);
}

Vector& Vector::operator+=(const Vector& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vector& Vector::operator-=(const Vector& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

Vector& Vector::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

Vector& Vector::operator/=(float scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}

bool Vector::operator==(const Vector& v) const {
    return x == v.x && y == v.y && z == v.z;
}

bool Vector::operator!=(const Vector& v) const {
    return !(*this == v);
}

// Methods
float Vector::length() const {
    return sqrt(x * x + y * y + z * z);
}

Vector Vector::normalize() const {
    float len = length();
    return Vector(x / len, y / len, z / len);
}

Vector Vector::cross(const Vector& v) const {
    return Vector(
        y * v.z - z * v.y,
        z * v.x - x * v.z,
        x * v.y - y * v.x
    );
}

float Vector::dot(const Vector& a, const Vector& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// Conversion to ofVec3f
ofVec3f Vector::toOfVec3f() const {
    return ofVec3f(x, y, z);
}

// Conversion to glm::vec3
glm::vec3 Vector::toGlmVec3() const {
    return glm::vec3(x, y, z);
}

// Conversion from glm::vec3
Vector Vector::fromGlmVec3(const glm::vec3& v) {
    return Vector(v.x, v.y, v.z);
}
