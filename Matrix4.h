#ifndef MATRIX4_H
#define MATRIX4_H

class Matrix4 {
public:
    // Matrix elements
    float x1, y1, z1, w1;
    float x2, y2, z2, w2;
    float x3, y3, z3, w3;
    float x4, y4, z4, w4;

    // Constructors
    Matrix4();
    Matrix4(float x1, float y1, float z1, float w1,
        float x2, float y2, float z2, float w2,
        float x3, float y3, float z3, float w3,
        float x4, float y4, float z4, float w4);

    // Basic Methods
    void print() const;
    float determinant() const;
    bool estInversible() const;
    Matrix4 inverse() const;
    Matrix4 transposee() const;

    // Operators
    Matrix4 operator+(const Matrix4& matrix) const;
    void operator+=(const Matrix4& matrix);
    Matrix4 operator-(const Matrix4& matrix) const;
    void operator-=(const Matrix4& matrix);
    Matrix4 operator*(float scalar) const;
    void operator*=(float scalar);
    Matrix4 operator*(const Matrix4& matrix) const;
    void operator*=(const Matrix4& matrix);
    bool operator==(const Matrix4& matrix) const;
};

#endif // MATRIX4_H
