#include "TestMatrix4.h"

// Test du constructeur par défaut
void TestMatrix4::testDefaultConstructor() {
    Matrix4 m;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            assert(m.matrix[i][j] == 0);
        }
    }
    std::cout << "Default constructor test passed.\n";
}

// Test du constructeur avec paramètres
void TestMatrix4::testParameterizedConstructor() {
    float tab[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            tab[i][j] = 4 * i + j;
        }
    }
    Matrix4 m(tab);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            assert(m.matrix[i][j] == 4 * i + j);
        }
    }
    std::cout << "Parameterized constructor test passed.\n";
}

// Test de l'opérateur d'addition
void TestMatrix4::testAdditionOperator() {
    // Composition de deux matrice remplie de 0 à N-1 et de N-1 à 0.
    float tab1[4][4];
    float tab2[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            tab1[i][j] = 4 * i + j;
            tab1[i][j] = 4 * (4 - i) + (4 - j);
        }
    }
    Matrix4 m1(tab1);
    Matrix4 m2(tab2);

    // Addition des deux tableaux qui ont servit à leur construction.
    float tab1PLUStab2[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            tab1PLUStab2[i][j] = tab1[i][j] + tab2[i][j];
        }
    }

    // Comparaison de la somme des deux matrices et de la somme des deux tableaux.
    assert(m1 + m2 == Matrix4(tab1PLUStab2));

    std::cout << "Addition operator test passed.\n";
}

// Test de l'opérateur de soustraction
void TestMatrix4::testSubtractionOperator() {
    // Composition de deux matrice remplie de 0 à N-1 et de N-1 à 0.
    float tab1[4][4];
    float tab2[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            tab1[i][j] = 4 * i + j;
            tab1[i][j] = 4 * (4 - i) + (4 - j);
        }
    }
    Matrix4 m1(tab1);
    Matrix4 m2(tab2);

    // Addition des deux tableaux qui ont servit à leur construction.
    float tab1PLUStab2[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            tab1PLUStab2[i][j] = tab1[i][j] - tab2[i][j];
        }
    }

    // Comparaison de la soustraction des deux matrices et de la somme des deux tableaux.
    assert(m1 - m2 == Matrix4(tab1PLUStab2));

    std::cout << "Addition operator test passed.\n";
}

// Test de la multiplication par un scalaire
void TestMatrix4::testScalarMultiplication() {
    // Composition de la matrice remplie de 0 à N-1.
    float tab[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            tab[i][j] = 4 * i + j;
        }
    }
    Matrix4 m(tab);

    // Multiplication par 2 du tableau.
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            tab[i][j] *= 2;
        }
    }

    // Comparaison de la multiplication par 2 de la matrice et du tableau multiplié par 2.
    assert(m * 2 == Matrix4(tab));

    std::cout << "Addition operator test passed.\n";
}

// Test de la transposée
void TestMatrix4::testTranspose() {
    // Composition de la matrice remplie de 0 à N-1.
    float tab[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            tab[i][j] = 4 * i + j;
        }
    }
    Matrix4 m(tab);

    float tab_inverse[4][4];
    // Transposé du tableau
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            tab_inverse[i][j] = tab[j][i];
        }
    }

    assert(m.transposee() == Matrix4(tab_inverse));

    std::cout << "Transpose test passed.\n";
}

// Test de l'inversion
void TestMatrix4::testInverse() {
    Matrix4 m = Matrix4::identite();
    Matrix4 result = m.inverse();
    assert(result == m); // La matrice identité est sa propre inverse

    m = Matrix4(4, 0, 1, 0, 7, 1, 0, 0, 2, 0, 1, 0, 3, 0, 0, 1);

    assert(m.estInversible());
    assert(m * m.inverse() == Matrix4::identite());
    std::cout << "Inverse test passed.\n";
}

void TestMatrix4::runTestMatrix4() {
    std::cout << "Start Test matrix4.\n";
    testDefaultConstructor();
    testParameterizedConstructor();
    testAdditionOperator();
    testSubtractionOperator();
    testScalarMultiplication();
    testTranspose();
    testInverse();

    std::cout << "All tests passed successfully.\n";
}