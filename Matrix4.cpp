#include <iostream>
#include "Matrix4.h"

// Constructors
Matrix4::Matrix4() {
    x1 = y1 = z1 = w1 = 0.0f;
    x2 = y2 = z2 = w2 = 0.0f;
    x3 = y3 = z3 = w3 = 0.0f;
    x4 = y4 = z4 = w4 = 0.0f;
}

Matrix4::Matrix4(float x1, float y1, float z1, float w1,
    float x2, float y2, float z2, float w2,
    float x3, float y3, float z3, float w3,
    float x4, float y4, float z4, float w4) {
    this->x1 = x1; this->y1 = y1; this->z1 = z1; this->w1 = w1;
    this->x2 = x2; this->y2 = y2; this->z2 = z2; this->w2 = w2;
    this->x3 = x3; this->y3 = y3; this->z3 = z3; this->w3 = w3;
    this->x4 = x4; this->y4 = y4; this->z4 = z4; this->w4 = w4;
}

// Basic Methods
void Matrix4::print() const {
    std::cout << x1 << " " << y1 << " " << z1 << " " << w1 << std::endl;
    std::cout << x2 << " " << y2 << " " << z2 << " " << w2 << std::endl;
    std::cout << x3 << " " << y3 << " " << z3 << " " << w3 << std::endl;
    std::cout << x4 << " " << y4 << " " << z4 << " " << w4 << std::endl;
}

float Matrix4::determinant() const {
    // Implement determinant calculation for a 4x4 matrix
    // This is a simplified placeholder
    return 0.0f;
}

bool Matrix4::estInversible() const {
    return determinant() != 0.0f;
}

Matrix4 Matrix4::inverse() const {
    // Implement inverse calculation for a 4x4 matrix
    // This is a simplified placeholder
    return Matrix4();
}

Matrix4 Matrix4::transposee() const {
    return Matrix4(x1, x2, x3, x4,
        y1, y2, y3, y4,
        z1, z2, z3, z4,
        w1, w2, w3, w4);
}

// Operators
Matrix4 Matrix4::operator+(const Matrix4& matrix) const {
    return Matrix4(x1 + matrix.x1, y1 + matrix.y1, z1 + matrix.z1, w1 + matrix.w1,
        x2 + matrix.x2, y2 + matrix.y2, z2 + matrix.z2, w2 + matrix.w2,
        x3 + matrix.x3, y3 + matrix.y3, z3 + matrix.z3, w3 + matrix.w3,
        x4 + matrix.x4, y4 + matrix.y4, z4 + matrix.z4, w4 + matrix.w4);
}

void Matrix4::operator+=(const Matrix4& matrix) {
    x1 += matrix.x1; y1 += matrix.y1; z1 += matrix.z1; w1 += matrix.w1;
    x2 += matrix.x2; y2 += matrix.y2; z2 += matrix.z2; w2 += matrix.w2;
    x3 += matrix.x3; y3 += matrix.y3; z3 += matrix.z3; w3 += matrix.w3;
    x4 += matrix.x4; y4 += matrix.y4; z4 += matrix.z4; w4 += matrix.w4;
}

Matrix4 Matrix4::operator-(const Matrix4& matrix) const {
    return Matrix4(x1 - matrix.x1, y1 - matrix.y1, z1 - matrix.z1, w1 - matrix.w1,
        x2 - matrix.x2, y2 - matrix.y2, z2 - matrix.z2, w2 - matrix.w2,
        x3 - matrix.x3, y3 - matrix.y3, z3 - matrix.z3, w3 - matrix.w3,
        x4 - matrix.x4, y4 - matrix.y4, z4 - matrix.z4, w4 - matrix.w4);
}

void Matrix4::operator-=(const Matrix4& matrix) {
    x1 -= matrix.x1; y1 -= matrix.y1; z1 -= matrix.z1; w1 -= matrix.w1;
    x2 -= matrix.x2; y2 -= matrix.y2; z2 -= matrix.z2; w2 -= matrix.w2;
    x3 -= matrix.x3; y3 -= matrix.y3; z3 -= matrix.z3; w3 -= matrix.w3;
    x4 -= matrix.x4; y4 -= matrix.y4; z4 -= matrix.z4; w4 -= matrix.w4;
}

Matrix4 Matrix4::operator*(float scalar) const {
    return Matrix4(x1 * scalar, y1 * scalar, z1 * scalar, w1 * scalar,
        x2 * scalar, y2 * scalar, z2 * scalar, w2 * scalar,
        x3 * scalar, y3 * scalar, z3 * scalar, w3 * scalar,
        x4 * scalar, y4 * scalar, z4 * scalar, w4 * scalar);
}

void Matrix4::operator*=(float scalar) {
    x1 *= scalar; y1 *= scalar; z1 *= scalar; w1 *= scalar;
    x2 *= scalar; y2 *= scalar; z2 *= scalar; w2 *= scalar;
    x3 *= scalar; y3 *= scalar; z3 *= scalar; w3 *= scalar;
    x4 *= scalar; y4 *= scalar; z4 *= scalar; w4 *= scalar;
}

Matrix4 Matrix4::operator*(const Matrix4& matrix) const {
    return Matrix4(
        x1 * matrix.x1 + y1 * matrix.x2 + z1 * matrix.x3 + w1 * matrix.x4,
        x1 * matrix.y1 + y1 * matrix.y2 + z1 * matrix.y3 + w1 * matrix.y4,
        x1 * matrix.z1 + y1 * matrix.z2 + z1 * matrix.z3 + w1 * matrix.z4,
        x1 * matrix.w1 + y1 * matrix.w2 + z1 * matrix.w3 + w1 * matrix.w4,

        x2 * matrix.x1 + y2 * matrix.x2 + z2 * matrix.x3 + w2 * matrix.x4,
        x2 * matrix.y1 + y2 * matrix.y2 + z2 * matrix.y3 + w2 * matrix.y4,
        x2 * matrix.z1 + y2 * matrix.z2 + z2 * matrix.z3 + w2 * matrix.z4,
        x2 * matrix.w1 + y2 * matrix.w2 + z2 * matrix.w3 + w2 * matrix.w4,

        x3 * matrix.x1 + y3 * matrix.x2 + z3 * matrix.x3 + w3 * matrix.x4,
        x3 * matrix.y1 + y3 * matrix.y2 + z3 * matrix.y3 + w3 * matrix.y4,
        x3 * matrix.z1 + y3 * matrix.z2 + z3 * matrix.z3 + w3 * matrix.z4,
        x3 * matrix.w1 + y3 * matrix.w2 + z3 * matrix.w3 + w3 * matrix.w4,

        x4 * matrix.x1 + y4 * matrix.x2 + z4 * matrix.x3 + w4 * matrix.x4,
        x4 * matrix.y1 + y4 * matrix.y2 + z4 * matrix.y3 + w4 * matrix.y4,
        x4 * matrix.z1 + y4 * matrix.z2 + z4 * matrix.z3 + w4 * matrix.z4,
        x4 * matrix.w1 + y4 * matrix.w2 + z4 * matrix.w3 + w4 * matrix.w4
    );
}

void Matrix4::operator*=(const Matrix4& matrix) {
    *this = *this * matrix;
}

bool Matrix4::operator==(const Matrix4& matrix) const {
    return x1 == matrix.x1 && y1 == matrix.y1 && z1 == matrix.z1 && w1 == matrix.w1 &&
        x2 == matrix.x2 && y2 == matrix.y2 && z2 == matrix.z2 && w2 == matrix.w2 &&
        x3 == matrix.x3 && y3 == matrix.y3 && z3 == matrix.z3 && w3 == matrix.w3 &&
        x4 == matrix.x4 && y4 == matrix.y4 && z4 == matrix.z4 && w4 == matrix.w4;
}
