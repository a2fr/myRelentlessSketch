#ifndef TESTMATRIX3_H
#define TESTMATRIX3_H

#include <iostream>
#include <cassert>
#include "Matrix3.h"*

class TestMatrix3
{

private:
    // Test du constructeur par d�faut
    void testDefaultConstructor();

    // Test du constructeur avec param�tres
    void testParameterizedConstructor();

    // Test de l'op�rateur d'addition
    void testAdditionOperator();

    // Test de l'op�rateur de soustraction
    void testSubtractionOperator();

    // Test de la multiplication par un scalaire
    void testScalarMultiplication();
    // Test de la transpos�e
    void testTranspose();

    // Test de l'inversion
    void testInverse();

public: 
    void runTestMatrix3();


};

#endif