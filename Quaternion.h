#ifndef QUATERNION_H
#define QUATERNION_H

#include "Vector.h"
#include <cmath>

// include toOfMatrix4
#include "ofMatrix4x4.h"

class Quaternion {
public:
    float w, x, y, z;

    // Constructors
    Quaternion();
    Quaternion(float w, float x, float y, float z);

    // Methods
    Quaternion negate() const;
    static Quaternion identity();
    float norme() const;
    Quaternion normalize() const;
    Quaternion conjugate() const;
    Quaternion inverse() const;
    Quaternion operator*(const Quaternion& q) const;
    Quaternion& operator*=(const Quaternion& q);
    Quaternion& operator+=(const Quaternion& q);
    Quaternion operator+(const Quaternion& q) const;
    Quaternion operator*(float scalar) const;
    Quaternion& operator*=(float scalar);
    Quaternion difference(const Quaternion& q) const;
    float dotProduct(const Quaternion& q) const;
    Quaternion exponentiate(float t) const;
    static Quaternion slerp(const Quaternion& q0, const Quaternion& q1, float t);
    // toOfMatrix4
	ofMatrix4x4 toOfMatrix4() const;
};

#endif // QUATERNION_H
