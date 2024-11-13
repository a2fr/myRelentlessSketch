#ifndef MATRIX3_H
#define MATRIX3_H


class Matrix3 {
public:
    float x1, y1, z1;
    float x2, y2, z2; // Représentation de la matrice
    float x3, y3, z3;

    Matrix3() {
        this->x1 = 0;
        this->x2 = 0;
        this->x3 = 0;
        this->y1 = 0;
        this->y2 = 0;
        this->y3 = 0;
        this->z1 = 0;
        this->z2 = 0;
        this->z3 = 0;
    }

    Matrix3(float x1, float x2, float x3, float y1, float y2, float y3, float z1, float z2, float z3) {
        this->x1 = x1;
        this->x2 = x2;
        this->x3 = x3;
        this->y1 = y1;
        this->y2 = y2;
        this->y3 = y3;
        this->z1 = z1;
        this->z2 = z2;
        this->z3 = z3;
    }

    Matrix3(float tab[3][3]) {
        this->x1 = tab[0][0];
        this->x2 = tab[1][0];
        this->x3 = tab[2][0];
        this->y1 = tab[0][1];
        this->y2 = tab[1][1];
        this->y3 = tab[2][1];
        this->z1 = tab[0][2];
        this->z2 = tab[1][2];
        this->z3 = tab[2][2];
    }

    static Matrix3 identite() {
        return Matrix3(1, 0, 0, 0, 1, 0, 0, 0, 1);
    }

    void print() const;

    float determinant() const;
    bool estInversible() const;
    Matrix3 inverse() const;
    Matrix3 transposee() const;
    Matrix3 exp(int n) const;

    Matrix3 operator+(Matrix3 const& matrix) const;
    void operator+=(Matrix3 const& matrix);
    Matrix3 operator-(Matrix3 const& matrix) const;
    void operator-=(Matrix3 const& matrix);
    Matrix3 operator*(float scalar) const;
    void operator*=(float scalar);
    Matrix3 operator*(Matrix3 const& matrix) const;
    void operator*=(Matrix3 const& matrix);
    bool operator==(Matrix3 const& matrix) const;
};

#endif
