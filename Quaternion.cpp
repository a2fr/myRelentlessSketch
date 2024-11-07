#include "Quaternion.h"

// Constructors
Quaternion::Quaternion() : w(1), x(0), y(0), z(0) {}

Quaternion::Quaternion(float w, float x, float y, float z) : w(w), x(x), y(y), z(z) {}

// Methods
Quaternion Quaternion::negate() const {
    return Quaternion(-w, -x, -y, -z);
}

Quaternion Quaternion::identity() {
    return Quaternion(1, 0, 0, 0);
}

float Quaternion::norme() const {
    return sqrt(w * w + x * x + y * y + z * z);
}

Quaternion Quaternion::normalize() const {
    float n = norme();
    return Quaternion(w / n, x / n, y / n, z / n);
}

Quaternion Quaternion::conjugate() const {
    return Quaternion(w, -x, -y, -z);
}

Quaternion Quaternion::inverse() const {
    float normSq = pow(norme(), 2);
    return Quaternion(w / normSq, -x / normSq, -y / normSq, -z / normSq);
}

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

Quaternion Quaternion::difference(const Quaternion& q) const {
    Quaternion c = conjugate();
    return q * c;
}

float Quaternion::dotProduct(const Quaternion& q) const {
    return w * q.w + x * q.x + y * q.y + z * q.z;
}

Quaternion Quaternion::exponentiate(float t) const {
    float alpha = std::acos(w);
    Vector v(x, y, z);

    float scalarPart = std::cos(t * alpha);
    Vector vectorPart = v * (std::sin(t * alpha) / std::sin(alpha));

    return Quaternion(scalarPart, vectorPart.x, vectorPart.y, vectorPart.z);
}

Quaternion Quaternion::slerp(const Quaternion& q0, const Quaternion& q1, float t) {
    Quaternion slerped = (q1 * q0.inverse()).exponentiate(t);
    return slerped * q0;
}

ofMatrix4x4 Quaternion::toOfMatrix4() const {
	ofMatrix4x4 matrix;
	matrix.makeIdentityMatrix();

	matrix(0, 0) = 1 - 2 * y * y - 2 * z * z;
	matrix(0, 1) = 2 * x * y - 2 * z * w;
	matrix(0, 2) = 2 * x * z + 2 * y * w;

	matrix(1, 0) = 2 * x * y + 2 * z * w;
	matrix(1, 1) = 1 - 2 * x * x - 2 * z * z;
	matrix(1, 2) = 2 * y * z - 2 * x * w;

	matrix(2, 0) = 2 * x * z - 2 * y * w;
	matrix(2, 1) = 2 * y * z + 2 * x * w;
	matrix(2, 2) = 1 - 2 * x * x - 2 * y * y;

	return matrix;
}
