#include "TestQuaternion.h"

void TestQuaternion::runTests() {
    testNegate();
    testIdentity();
    testNorme();
    testNormalize();
    testConjugate();
    testInverse();
    testMultiplication();
    testDifference();
    testDotProduct();
    testExponentiate();
    testSlerp();

    std::cout << "Tous les tests sont termines." << std::endl;
}

void TestQuaternion::testNegate() {
    Quaternion q(1, 2, 3, 4);
    Quaternion negated = q.negate();
    if (negated.w == -1 && negated.x == -2 && negated.y == -3 && negated.z == -4) {
        printResult("testNegate", true);
    }
    else {
        printResult("testNegate", false);
    }
}

void TestQuaternion::testIdentity() {
    Quaternion q = q.identity();
    if (q.w == 1 && q.x == 0 && q.y == 0 && q.z == 0) {
        printResult("testIdentity", true);
    }
    else {
        printResult("testIdentity", false);
    }
    
}

void TestQuaternion::testNorme() {
    Quaternion q(1, 2, 2, 2);
    if (std::abs(q.norme() - 3.60555f) < 0.0001f) {
        printResult("testNorme", true);
    }
    else {
        printResult("testNorme", false);
    }
}

void TestQuaternion::testNormalize() {
    Quaternion q(1, 2, 2, 2);
    Quaternion normalized = q.normalize();
    if (std::abs(normalized.norme() - 1.0f) < 0.0001f) {
        printResult("testNormalize", true);
    }
    else {
        printResult("testNormalize", false);
    }
}

void TestQuaternion::testConjugate() {
    Quaternion q(1, 2, 3, 4);
    Quaternion conjugated = q.conjugate();
    if (conjugated.w == 1 && conjugated.x == -2 && conjugated.y == -3 && conjugated.z == -4) {
        printResult("testConjugate", true);
    }
    else {
        printResult("testConjugate", false);
    }
}

void TestQuaternion::testInverse() {
    Quaternion q(3, 0, 4, 0); // Choix d'un quaternion avec norme entière 5
    Quaternion inversed = q.inverse();
    
    // Utilisation d'une petite tolérance pour gérer les erreurs numériques
    if (inversed.w == 0.6f && inversed.x == -0.0f && inversed.y == -0.8f && inversed.z == -0.0f) {
        printResult("testInverse", true);
    }
    else {
        printResult("testInverse", false);
    }
}

void TestQuaternion::testMultiplication() {
    Quaternion q1(1, 0, 1, 0);
    Quaternion q2(1, 0.5, 0.5, 0.75);
    Quaternion result = q1 * q2;
    if (result.w == 0.5f && result.x == 1.25 && result.y == 1.5 && result.z == 0.25) {
        printResult("testMultiplication", true);
    }
    else {
        printResult("testMultiplication", false);
    }
}

void TestQuaternion::testDifference() {
    Quaternion q1(1, 0, 1, 0);
    Quaternion q2(0, 1, 0, 0);
    Quaternion difference = q1.difference(q2);
    if(difference.w == 0 && difference.x == 1 && difference.y == 0 && difference.z ==-1){
        printResult("testDiff", true);
    }
    else {
        printResult("testDiff", false);
    }
}

void TestQuaternion::testDotProduct() {
    Quaternion q1(1, 2, 3, 4);
    Quaternion q2(2, 2, 2, 2);
    float dot = q1.dotProduct(q2);
    if (std::abs(dot - 20.0f) < 0.0001f) {
        printResult("testDotProduct", true);
    }
    else {
        printResult("testDotProduct", false);
    }
}

void TestQuaternion::testExponentiate() {
    Quaternion q(0.7071f, 0.7071f, 0, 0);
    Quaternion expResult = q.exponentiate(0.5f);
    if(std::abs(expResult.w - 0.9238f) < 0.0001f) {
        printResult("testExponentiate", true);
    }
    else {
        printResult("testExponentiate", false);
    }
    
}

void TestQuaternion::testSlerp() {
    Quaternion q0(1, 0, 0, 0);
    Quaternion q1(0, 1, 0, 0);
    Quaternion result = result.slerp(q0, q1, 0.5f);
    if (std::abs(result.w - 0.7071f) < 0.0001f && std::abs(result.x - 0.7071f) < 0.0001f &&
        std::abs(result.y) < 0.0001f && std::abs(result.z) < 0.0001f) {
        printResult("testSlerp", true);
    }
    else {
        printResult("testSlerp", false);
    }
}

void TestQuaternion::printResult(const std::string& testName, bool passed) {
    if (passed) {
        std::cout << testName << " passed." << std::endl;
    }
    else {
        std::cout << testName << " failed." << std::endl;
    }
}
