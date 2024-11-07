#include <iostream>
#include "Matrix3.h"

float Matrix3::determinant() const {
    return x1 * (y2 * z3 - z2 * y3) - x2 * (y1 * z3 - y3 * z1) + x3 * (y1 * z2 - y2 * z1);
}

bool Matrix3::estInversible() const {
    return determinant() != 0;
}

Matrix3 Matrix3::inverse() const {
    // computes the inverse of a matrix m
    double det = determinant();

    double invdet = 1 / det;

    Matrix3 minv; // inverse of matrix m
    minv.x1 = (y2 * z3 - z2 * y3) * invdet;
    minv.x2 = (x3 * z2 - x2 * z3) * invdet;
    minv.x3 = (x2 * y3 - x3 * y2) * invdet;
    minv.y1 = (y3 * z1 - y1 * z3) * invdet;
    minv.y2 = (x1 * z3 - x3 * z1) * invdet;
    minv.y3 = (y1 * x3 - x1 * y3) * invdet;
    minv.z1 = (y1 * z2 - z1 * y2) * invdet;
    minv.z2 = (z1 * x2 - x1 * z2) * invdet;
    minv.z3 = (x1 * y2 - y1 * x2) * invdet;

    return minv;
}

void Matrix3::print() const {
    std::cout << x1 << ", " << y1 << ", " << z1 << "\n";
    std::cout << x2 << ", " << y2 << ", " << z2 << "\n";
    std::cout << x3 << ", " << y3 << ", " << z3 << "\n";
}

/*
x1, y1, z1    x1, x2, x3
x2, y2, z2 => y1, y2, y3
x3, y3, z3    z1, z2, z3
*/
Matrix3 Matrix3::transposee() const {
    Matrix3 tranm;
    tranm.x1 = x1;
    tranm.y1 = x2;
    tranm.z1 = x3;
    tranm.x2 = y1;
    tranm.y2 = y2;
    tranm.z2 = y3;
    tranm.x3 = z1;
    tranm.y3 = z2;
    tranm.z3 = z3;

    return tranm;
}

Matrix3 Matrix3::exp(int n) const {
    Matrix3 res = Matrix3(*this);
    for (int i = 0; i < n; i++) {
        res *= *this;
    }
    return res;
}

Matrix3 Matrix3::operator+(Matrix3 const& matrix) const {
    Matrix3 result;
    result.x1 = x1 + matrix.x1;
    result.x2 = x2 + matrix.x2;
    result.x3 = x3 + matrix.x3;
    result.y1 = y1 + matrix.y1;
    result.y2 = y2 + matrix.y2;
    result.y3 = y3 + matrix.y3;
    result.z1 = z1 + matrix.z1;
    result.z2 = z2 + matrix.z2;
    result.z3 = z3 + matrix.z3;

    return result;
}

void Matrix3::operator+=(Matrix3 const& matrix) {
    *this = *this + matrix;
}

Matrix3 Matrix3::operator-(Matrix3 const& matrix) const {
    Matrix3 result;
    result.x1 = x1 - matrix.x1;
    result.x2 = x2 - matrix.x2;
    result.x3 = x3 - matrix.x3;
    result.y1 = y1 - matrix.y1;
    result.y2 = y2 - matrix.y2;
    result.y3 = y3 - matrix.y3;
    result.z1 = z1 - matrix.z1;
    result.z2 = z2 - matrix.z2;
    result.z3 = z3 - matrix.z3;

    return result;
}

void Matrix3::operator-=(Matrix3 const& matrix) {
    *this = *this - matrix;
}

Matrix3 Matrix3::operator*(float scalar) const {
    Matrix3 result;
    result.x1 = x1 * scalar;
    result.x2 = x2 * scalar;
    result.x3 = x3 * scalar;
    result.y1 = y1 * scalar;
    result.y2 = y2 * scalar;
    result.y3 = y3 * scalar;
    result.z1 = z1 * scalar;
    result.z2 = z2 * scalar;
    result.z3 = z3 * scalar;

    return result;
}

void Matrix3::operator*=(float scalar) {
    *this = *this * scalar;
}

Matrix3 Matrix3::operator*(Matrix3 const& matrix) const {
    Matrix3 result;
    result.x1 = x1 * matrix.x1 + y1 * matrix.x2 + z1 * matrix.x3;
    result.x2 = x2 * matrix.x1 + y2 * matrix.x2 + z2 * matrix.x3;
    result.x3 = x3 * matrix.x1 + y3 * matrix.x2 + z3 * matrix.x3;
    result.y1 = x1 * matrix.y1 + y1 * matrix.y2 + z1 * matrix.y3;
    result.y2 = x2 * matrix.y1 + y2 * matrix.y2 + z2 * matrix.y3;
    result.y3 = x3 * matrix.y1 + y3 * matrix.y2 + z3 * matrix.y3;
    result.z1 = x1 * matrix.z1 + y1 * matrix.z2 + z1 * matrix.z3;
    result.z2 = x2 * matrix.z1 + y2 * matrix.z2 + z2 * matrix.z3;
    result.z3 = x3 * matrix.z1 + y3 * matrix.z2 + z3 * matrix.z3;

    return result;
}

void Matrix3::operator*=(Matrix3 const& matrix) {
    *this = *this * matrix;
}

bool Matrix3::operator==(Matrix3 const& matrix) const {
    return this->x1 == matrix.x1
        && this->x2 == matrix.x2
        && this->x3 == matrix.x3
        && this->y1 == matrix.y1
        && this->y2 == matrix.y2
        && this->y3 == matrix.y3
        && this->z1 == matrix.z1
        && this->z2 == matrix.z2
        && this->z3 == matrix.z3;
}

Matrix3 Matrix3::identity() {
	return Matrix3(1, 0, 0, 0, 1, 0, 0, 0, 1);
}