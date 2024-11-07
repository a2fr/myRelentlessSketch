/*#include <iostream>
#include <cassert>
#include "Matrix3.h"

// Test du constructeur par défaut
void testDefaultConstructor() {
    Matrix3 m;
    assert(m.x1 == 0);
    assert(m.x2 == 0);
    assert(m.x3 == 0);
    assert(m.y1 == 0);
    assert(m.y2 == 0);
    assert(m.y3 == 0);
    assert(m.z1 == 0);
    assert(m.z2 == 0);
    assert(m.z3 == 0);
    std::cout << "Default constructor test passed.\n";
}

// Test du constructeur avec paramètres
void testParameterizedConstructor() {
    Matrix3 m(1, 2, 3, 4, 5, 6, 7, 8, 9);
    assert(m.x1 == 1);
    assert(m.x2 == 2);
    assert(m.x3 == 3);
    assert(m.y1 == 4);
    assert(m.y2 == 5);
    assert(m.y3 == 6);
    assert(m.z1 == 7);
    assert(m.z2 == 8);
    assert(m.z3 == 9);
    std::cout << "Parameterized constructor test passed.\n";
}

// Test de l'opérateur d'addition
void testAdditionOperator() {
    Matrix3 m1(1, 2, 3, 4, 5, 6, 7, 8, 9);
    Matrix3 m2(9, 8, 7, 6, 5, 4, 3, 2, 1);
    Matrix3 result = m1 + m2;

    assert(result.x1 == 10);
    assert(result.x2 == 10);
    assert(result.x3 == 10);
    assert(result.y1 == 10);
    assert(result.y2 == 10);
    assert(result.y3 == 10);
    assert(result.z1 == 10);
    assert(result.z2 == 10);
    assert(result.z3 == 10);
    std::cout << "Addition operator test passed.\n";
}

// Test de l'opérateur de soustraction
void testSubtractionOperator() {
    Matrix3 m1(1, 2, 3, 4, 5, 6, 7, 8, 9);
    Matrix3 m2(9, 8, 7, 6, 5, 4, 3, 2, 1);
    Matrix3 result = m1 - m2;

    assert(result.x1 == -8);
    assert(result.x2 == -6);
    assert(result.x3 == -4);
    assert(result.y1 == -2);
    assert(result.y2 == 0);
    assert(result.y3 == 2);
    assert(result.z1 == 4);
    assert(result.z2 == 6);
    assert(result.z3 == 8);
    std::cout << "Subtraction operator test passed.\n";
}

// Test de la multiplication par un scalaire
void testScalarMultiplication() {
    Matrix3 m(1, 2, 3, 4, 5, 6, 7, 8, 9);
    Matrix3 result = m * 2.0f;

    assert(result.x1 == 2);
    assert(result.x2 == 4);
    assert(result.x3 == 6);
    assert(result.y1 == 8);
    assert(result.y2 == 10);
    assert(result.y3 == 12);
    assert(result.z1 == 14);
    assert(result.z2 == 16);
    assert(result.z3 == 18);
    std::cout << "Scalar multiplication test passed.\n";
}

// Test de la transposée
void testTranspose() {
    Matrix3 m(1, 2, 3, 4, 5, 6, 7, 8, 9);
    Matrix3 result = m.transposee();

    assert(result.x1 == 1);
    assert(result.y1 == 2);
    assert(result.z1 == 3);
    assert(result.x2 == 4);
    assert(result.y2 == 5);
    assert(result.z2 == 6);
    assert(result.x3 == 7);
    assert(result.y3 == 8);
    assert(result.z3 == 9);
    std::cout << "Transpose test passed.\n";
}

// Test de l'inversion
void testInverse() {
    Matrix3 m(1, 0, 0, 0, 1, 0, 0, 0, 1);
    Matrix3 result = m.inverse();
    assert(result == m); // La matrice identité est sa propre inverse

    Matrix3 singularMatrix(1, 2, 3, 4, 5, 6, 7, 8, 9); // Déterminant nul
    assert(!singularMatrix.estInversible());
    std::cout << "Inverse test passed.\n";
}

int main() {
    testDefaultConstructor();
    testParameterizedConstructor();
    testAdditionOperator();
    testSubtractionOperator();
    testScalarMultiplication();
    testTranspose();
    testInverse();

    std::cout << "All tests passed successfully.\n";
    return 0;
}*/