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
    float norm = norme();
    Quaternion conjug = conjugate();

    return Quaternion(conjug.w / norm, conjug.x / norm, conjug.y / norm, conjug.z / norm);
}

//Quaternion Quaternion::operator*(const Quaternion& q) const
//{
//    float w1 = w;
//    Vector v1 = Vector(x, y, z);
//    float w2 = q.w;
//    Vector v2 = Vector(q.x, q.y, q.z);
//
//    // Calcul de la partie scalaire
//    float scalarPart = w1 * w2 - produitScalaire(v1, v2);  // produit scalaire entre les vecteurs
//
//    // Calcul de la partie vectorielle
//    Vector vectorPart = (v2 * w1) + (v1 * w2) + produitVectoriel(v1, v2);  // produit vectoriel
//
//    return Quaternion(scalarPart, vectorPart.x, vectorPart.y, vectorPart.z);
//}


Quaternion Quaternion::operator*(const Quaternion& q) const {
    return Quaternion(
        w * q.w - x * q.x - y * q.y - z * q.z,
        w * q.x + x * q.w + y * q.z - z * q.y,
        w * q.y - x * q.z + y * q.w + z * q.x,
        w * q.z + x * q.y - y * q.x + z * q.w
    );
}

Quaternion& Quaternion::operator*=(const Quaternion& q) {
    *this = *this * q;
    return *this;
}

Quaternion& Quaternion::operator+=(const Quaternion& q) {
    w += q.w;
    x += q.x;
    y += q.y;
    z += q.z;
    return *this;
}

Quaternion Quaternion::operator+(const Quaternion& q) const {
    return Quaternion(w + q.w, x + q.x, y + q.y, z + q.z);
}

Quaternion Quaternion::operator*(float scalar) const {
    return Quaternion(w * scalar, x * scalar, y * scalar, z * scalar);
}

Quaternion& Quaternion::operator*=(float scalar) {
    w *= scalar;
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
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
    Matrix4 mat;

    // Calculer les termes réutilisés pour optimiser les calculs
    float xx = x * x;
    float yy = y * y;
    float zz = z * z;
    float xy = x * y;
    float xz = x * z;
    float yz = y * z;
    float wx = w * x;
    float wy = w * y;
    float wz = w * z;

    // Remplir la matrice de rotation 4x4
    mat.matrix[0][0] = 1.0f - 2.0f * (yy + zz);
    mat.matrix[0][1] = 2.0f * (xy - wz);
    mat.matrix[0][2] = 2.0f * (xz + wy);
    mat.matrix[0][3] = 0.0f;

    mat.matrix[1][0] = 2.0f * (xy + wz);
    mat.matrix[1][1] = 1.0f - 2.0f * (xx + zz);
    mat.matrix[1][2] = 2.0f * (yz - wx);
    mat.matrix[1][3] = 0.0f;

    mat.matrix[2][0] = 2.0f * (xz - wy);
    mat.matrix[2][1] = 2.0f * (yz + wx);
    mat.matrix[2][2] = 1.0f - 2.0f * (xx + yy);
    mat.matrix[2][3] = 0.0f;

    mat.matrix[3][0] = 0.0f;
    mat.matrix[3][1] = 0.0f;
    mat.matrix[3][2] = 0.0f;
    mat.matrix[3][3] = 1.0f;

    return mat;
}



