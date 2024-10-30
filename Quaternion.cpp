#include "Quaternion.h"

Quaternion Quaternion::negate() const
{
    return Quaternion(-w, -x, -y, -z);
}

Quaternion Quaternion::identity() const
{
    return Quaternion(1, 0, 0, 0);
}

float Quaternion::norme() const
{
    return sqrt(w * w + x * x + y * y + z * z);
}

Quaternion Quaternion::normalize() const
{
    float n = norme();
    return Quaternion(w / n, x / n, y / n, z / n);
}

Quaternion Quaternion::conjugate() const
{
    return Quaternion(w, -x, -y, -z);
}

Quaternion Quaternion::inverse() const
{
    float normSq = pow(norme(),2);
    return Quaternion(w / normSq, -x / normSq, -y / normSq, -z / normSq);
}

Quaternion Quaternion::operator*(const Quaternion& q) const
{
    float w1 = w;
    Vector v1 = Vector(x, y, z);
    float w2 = q.w;
    Vector v2 = Vector(q.x, q.y, q.z);

    float scalarPart = w1 * w2;
    Vector vectorPart = -((v2*w1 +  v1*w2 + produitVectoriel(v1, v2)) * produitScalaire(v1, v2));

    return Quaternion(scalarPart, vectorPart.x, vectorPart.y, vectorPart.z);
}

Quaternion Quaternion::difference(const Quaternion& q) const
{
    Quaternion c = conjugate();
    return q*c ;
}

float Quaternion::dotProduct(const Quaternion& q) const
{
    return w * q.w + x * q.x + y * q.y + z * q.z;
}

Quaternion Quaternion::exponentiate(float t) const
{
    float alpha = std::acos(w);
    Vector v = Vector(x, y, z);

    float scalarPart = std::cos(t * alpha);
    Vector vectorPart = v * (std::sin(t * alpha) / std::sin(alpha));

    return Quaternion(scalarPart, vectorPart.x, vectorPart.y, vectorPart.z);
}

Quaternion Quaternion::slerp(const Quaternion& q0, const Quaternion& q1, float t)
{
    Quaternion slerped = (q1 * q0.inverse()).exponentiate(t);
    return slerped * q0;
}

Matrix4 Quaternion::toMatrix4() const
{
    return Matrix4();
}



