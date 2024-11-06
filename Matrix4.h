#ifndef MATRIX4_H
#define MATRIX4_H

#include "Matrix3.h"

class Matrix4 {
public:
    float matrix[4][4]; // matrix[0][0] est la valeur en haut à gauche et matrix[3][3] est la valeur en bas à droite

    Matrix4() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                matrix[i][j] = 0;
            }
        }
    }

    Matrix4(float x1, float x2, float x3, float x4, float y1, float y2, float y3, float y4, float z1, float z2, float z3, float z4, float w1, float w2, float w3, float w4) {
        matrix[0][0] = x1;
        matrix[1][0] = x2;
        matrix[2][0] = x3;
        matrix[3][0] = x4;

        matrix[0][1] = y1;
        matrix[1][1] = y2;
        matrix[2][1] = y3;
        matrix[3][1] = y4;

        matrix[0][2] = z1;
        matrix[1][2] = z2;
        matrix[2][2] = z3;
        matrix[3][2] = z4;

        matrix[0][3] = w1;
        matrix[1][3] = w2;
        matrix[2][3] = w3;
        matrix[3][3] = w4;
    }

    Matrix4(float tab[4][4]) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                matrix[i][j] = tab[i][j];
            }
        }
    }

    static Matrix4 identite() {
        return Matrix4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
    }

    void print() const;

    float determinant() const;
    bool estInversible() const;
    Matrix4 cofactorMatrix4x4() const;
    Matrix4 inverse() const;
    Matrix4 transposee() const;
    Matrix4 exp(int n) const;

    Matrix4 operator+(Matrix4 const& other) const;
    void operator+=(Matrix4 const& other);
    Matrix4 operator-(Matrix4 const& other) const;
    void operator-=(Matrix4 const& other);
    Matrix4 operator*(float scalar) const;
    void operator*=(float scalar);
    Matrix4 operator*(Matrix4 const& other) const;
    void operator*=(Matrix4 const& other);
    bool operator==(Matrix4 const& other) const;
};


#endif