#pragma once

#include "Vector.h"
#include "Matrix4.h"

class Quaternion
{
public:
	float w, x, y, z;

    Quaternion() : w(1), x(0), y(0), z(0) {}
    Quaternion(float w, float x, float y, float z) : w(w), x(x), y(y), z(z) {}
    Quaternion(float angle, const Vector& axis) {
        float halfAngle = angle * 0.5f;
        w = cos(halfAngle);
        float s = sin(halfAngle);
        x = axis.x * s;
        y = axis.y * s;
        z = axis.z * s;
    }

    //Négation
    Quaternion negate()const;

    //Identité (retourne le quaternion Identité)
    Quaternion identity() const;
    
    //Norme 
    float norme() const;
    Quaternion normalize() const;

    //Conjugué
    Quaternion conjugate() const;
    //Inverse
    Quaternion inverse() const;

    // Multiplication de quaternions
    Quaternion operator*(const Quaternion& q) const;

    //diférence
    Quaternion difference(const Quaternion& q) const;

    //Produit sclaire
    float dotProduct(const Quaternion& q) const;

    //Exponentiation
    Quaternion exponentiate(float t) const;

    //Slerp
    Quaternion slerp(const Quaternion& q0, const Quaternion& q1, float t);

    Matrix4 toMatrix4() const;
};

