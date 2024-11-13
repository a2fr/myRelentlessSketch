#pragma once
#pragma once

#include "Quaternion.h"
#include "Matrix4.h"
#include <cassert>
#include <iostream>

class TestQuaternion {
public:
    void runTests();

private:
    void testNegate();
    void testIdentity();
    void testNorme();
    void testNormalize();
    void testConjugate();
    void testInverse();
    void testMultiplication();
    void testDifference();
    void testDotProduct();
    void testExponentiate();
    void testSlerp();
    void testToMatrix4();

    void printResult(const std::string& testName, bool passed);
};
