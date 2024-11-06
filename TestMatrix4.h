#pragma once

#include <iostream>
#include <cassert>
#include "Matrix4.h"

class TestMatrix4
{
private:
    // Test du constructeur par défaut
    void testDefaultConstructor();

    // Test du constructeur avec paramètres
    void testParameterizedConstructor();

    // Test de l'opérateur d'addition
    void testAdditionOperator();

    // Test de l'opérateur de soustraction
    void testSubtractionOperator();

    // Test de la multiplication par un scalaire
    void testScalarMultiplication();

    // Test de la transposée
    void testTranspose();

    // Test de l'inversion
    void testInverse();

public:
    void runTestMatrix4();
};

