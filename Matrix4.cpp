#include <iostream>
#include "Matrix4.h"

float Matrix4::determinant() const {
    float det = 0;
    det += matrix[0][0] * Matrix3(matrix[1][1], matrix[1][2], matrix[1][3], matrix[2][1], matrix[2][2], matrix[2][3], matrix[3][1], matrix[3][2], matrix[3][3]).determinant();
    det -= matrix[0][1] * Matrix3(matrix[1][0], matrix[1][2], matrix[1][3], matrix[2][0], matrix[2][2], matrix[2][3], matrix[3][0], matrix[3][2], matrix[3][3]).determinant();
    det += matrix[0][2] * Matrix3(matrix[1][0], matrix[1][1], matrix[1][3], matrix[2][0], matrix[2][1], matrix[2][3], matrix[3][0], matrix[3][1], matrix[3][3]).determinant();
    det -= matrix[0][3] * Matrix3(matrix[1][0], matrix[1][1], matrix[1][2], matrix[2][0], matrix[2][1], matrix[2][2], matrix[3][0], matrix[3][1], matrix[3][2]).determinant();
    return det;
}

bool Matrix4::estInversible() const {
    return determinant() != 0;
}

// Fonction pour calculer la matrice des cofacteurs de 4x4
Matrix4 Matrix4::cofactorMatrix4x4() const {
    float cofactors[4][4];
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            // Création de la sous-matrice 3x3 pour le cofacteur (i, j)
            float subMatrix[3][3];
            int subRow = 0;
            for (int row = 0; row < 4; ++row) {
                if (row == i) continue; // Ignore la ligne i
                int subCol = 0;
                for (int col = 0; col < 4; ++col) {
                    if (col == j) continue; // Ignore la colonne j
                    subMatrix[subRow][subCol] = this->matrix[row][col];
                    subCol++;
                }
                subRow++;
            }
            // Calcul du cofacteur
            cofactors[i][j] = ((i + j) % 2 == 0 ? 1 : -1) * Matrix3(subMatrix).determinant();
        }
    }
    return Matrix4(cofactors);
}

Matrix4 Matrix4::inverse() const {
    float det = determinant();
    if (det == 0) {
        std::cerr << "La matrice n'est pas inversible." << std::endl;
        return Matrix4();
    }

    // Calcul de la matrice des cofacteurs
    Matrix4 cofactors = cofactorMatrix4x4();

    // Transpose de la matrice des cofacteurs pour obtenir la matrice adjointe
    cofactors = cofactors.transposee();

    Matrix4 inverse(cofactors);
    inverse *= (1 / det);

    return inverse;
}

void Matrix4::print() const {
    for (int i = 0; i < 4; i++) {
        std::cout << matrix[i][0] << ", " << matrix[i][1] << ", " << matrix[i][2] << ", " << matrix[i][3] << "\n";
    }
}

Matrix4 Matrix4::transposee() const {
    float m[4][4];
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            m[i][j] = this->matrix[j][i];
        }
    }

    return Matrix4(m);
}

Matrix4 Matrix4::exp(int n) const {
    Matrix4 res = Matrix4(*this);
    for (int i = 0; i < n; i++) {
        res *= *this;
    }
    return res;
}

ofMatrix4x4 Matrix4::toOfMatrix4x4() const
{
    ofMatrix4x4 result;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result(i, j) = matrix[i][j];  // Copie chaque élément dans ofMatrix4x4
        }
    }

    return result;
}

Matrix4 Matrix4::operator+(Matrix4 const& other) const {
    float result[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result[i][j] = this->matrix[i][j] + other.matrix[i][j];
        }
    }

    return Matrix4(result);
}

void Matrix4::operator+=(Matrix4 const& other) {
    *this = *this + matrix;
}

Matrix4 Matrix4::operator-(Matrix4 const& other) const {
    float result[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result[i][j] = this->matrix[i][j] - other.matrix[i][j];
        }
    }

    return Matrix4(result);
}

void Matrix4::operator-=(Matrix4 const& other) {
    *this = *this - matrix;
}

Matrix4 Matrix4::operator*(float scalar) const {
    float result[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result[i][j] = this->matrix[i][j] * scalar;
        }
    }

    return Matrix4(result);
}

void Matrix4::operator*=(float scalar) {
    *this = *this * scalar;
}

Matrix4 Matrix4::operator*(Matrix4 const& other) const {
    float result[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result[i][j] = this->matrix[i][0] * other.matrix[0][j] + this->matrix[i][1] * other.matrix[1][j] + this->matrix[i][2] * other.matrix[2][j] + this->matrix[i][3] * other.matrix[3][j];
        }
    }

    return Matrix4(result);
}

void Matrix4::operator*=(Matrix4 const& other) {
    *this = *this * matrix;
}

bool Matrix4::operator==(Matrix4 const& other) const {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (this->matrix[i][j] != other.matrix[i][j]) {
                return false;
            }
        }
    }
    return true;
}
