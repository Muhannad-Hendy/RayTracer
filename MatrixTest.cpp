#include "gmock/gmock.h"
#include "Matrix.h"
#include "Tuple.h"

using namespace testing;

class MatrixFeature : public Test {

};

TEST_F(MatrixFeature, ConstructingAndInspectingFourByFourMatrix) {
    Matrix m{4,4};
    m.set(0,0,1);
    m.set(0,1,2);
    m.set(0,2,3);
    m.set(0,3,4);
    m.set(1,0,5.5);
    m.set(1,1,6.5);
    m.set(1,2,7.5);
    m.set(1,3,8.5);
    m.set(2,0,9);
    m.set(2,1,10);
    m.set(2,2,11);
    m.set(2,3,12);
    m.set(3,0,13.5);
    m.set(3,1,14.5);
    m.set(3,2,15.5);
    m.set(3,3,16.5);
    ASSERT_THAT(m.get(0,0), Eq(1));
    ASSERT_THAT(m.get(0,3), Eq(4));
    ASSERT_THAT(m.get(1,0), Eq(5.5));
    ASSERT_THAT(m.get(1,2), Eq(7.5));
    ASSERT_THAT(m.get(2,2), Eq(11));
    ASSERT_THAT(m.get(3,0), Eq(13.5));
    ASSERT_THAT(m.get(3,2), Eq(15.5));
}

TEST_F(MatrixFeature, ConstructingAndInspectingTwoByTwoMatrix){
    Matrix m(2,2);
    m.set(0,0,-3);
    m.set(0,1,5);
    m.set(1,0,1);
    m.set(1,1,-2);
    ASSERT_THAT(m.get(0,0), Eq(-3));
    ASSERT_THAT(m.get(0,1), Eq(5));
    ASSERT_THAT(m.get(1,0), Eq(1));
    ASSERT_THAT(m.get(1,1), Eq(-2));
}

TEST_F(MatrixFeature, ConstructingAndInspectingThreeByThreeMatrix){
    Matrix m(3,3);
    m.set(0,0,-3);
    m.set(0,1,5);
    m.set(0,2,0);
    m.set(1,0,1);
    m.set(1,1,-2);
    m.set(1,2,-7);
    m.set(2,0, 0);
    m.set(2,1,1);
    m.set(2,2,1);
    ASSERT_THAT(m.get(0,0), Eq(-3));
    ASSERT_THAT(m.get(1,1), Eq(-2));
    ASSERT_THAT(m.get(2,2), Eq(1));
}

TEST_F(MatrixFeature, CheckingMatricesForEquality){
    Matrix A(4,4);
    A.set(0,0,1);
    A.set(0,1,2);
    A.set(0,2,3);
    A.set(0,3,4);
    A.set(1,0,5);
    A.set(1,1,6);
    A.set(1,2,7);
    A.set(1,3,8);
    A.set(2,0,9);
    A.set(2,1,8);
    A.set(2,2,7);
    A.set(2,3,6);
    A.set(3,0,5);
    A.set(3,1,4);
    A.set(3,2,3);
    A.set(3,3,2);

    Matrix B(4,4);
    B.set(0,0,1);
    B.set(0,1,2);
    B.set(0,2,3);
    B.set(0,3,4);
    B.set(1,0,5);
    B.set(1,1,6);
    B.set(1,2,7);
    B.set(1,3,8);
    B.set(2,0,9);
    B.set(2,1,8);
    B.set(2,2,7);
    B.set(2,3,6);
    B.set(3,0,5);
    B.set(3,1,4);
    B.set(3,2,3);
    B.set(3,3,2);

    Matrix C(4,4);
    C.set(0,0,0);
    C.set(0,1,2);
    C.set(0,2,3);
    C.set(0,3,4);
    C.set(1,0,5);
    C.set(1,1,6);
    C.set(1,2,7);
    C.set(1,3,8);
    C.set(2,0,9);
    C.set(2,1,8);
    C.set(2,2,7);
    C.set(2,3,6);
    C.set(3,0,5);
    C.set(3,1,4);
    C.set(3,2,3);
    C.set(3,3,2);

    ASSERT_THAT(A == B, true);
    ASSERT_THAT(B == C, false);
}

TEST_F(MatrixFeature, CheckMatricesForFloatsEquality){
    Matrix D(1,1);
    D.set(0,0,1.23456);
    Matrix E(1,1);
    E.set(0,0,1.23457);
    Matrix F(1,1);
    F.set(0,0, 1.23478);

    ASSERT_THAT(D == E, true);
    ASSERT_THAT(F == D, false);
}

TEST_F(MatrixFeature, MultiplyingTwoMatrices){
    Matrix A(4,4);
    A.set(0,0,1);
    A.set(0,1,2);
    A.set(0,2,3);
    A.set(0,3,4);
    A.set(1,0,5);
    A.set(1,1,6);
    A.set(1,2,7);
    A.set(1,3,8);
    A.set(2,0,9);
    A.set(2,1,8);
    A.set(2,2,7);
    A.set(2,3,6);
    A.set(3,0,5);
    A.set(3,1,4);
    A.set(3,2,3);
    A.set(3,3,2);

    Matrix B(4,4);
    B.set(0,0,-2);
    B.set(0,1,1);
    B.set(0,2,2);
    B.set(0,3,3);
    B.set(1,0,3);
    B.set(1,1,2);
    B.set(1,2,1);
    B.set(1,3,-1);
    B.set(2,0,4);
    B.set(2,1,3);
    B.set(2,2,6);
    B.set(2,3,5);
    B.set(3,0,1);
    B.set(3,1,2);
    B.set(3,2,7);
    B.set(3,3,8);

    Matrix C(4,4);
    C.set(0,0, 20);
    C.set(0,1,22);
    C.set(0,2,50);
    C.set(0,3,48);
    C.set(1,0,44);
    C.set(1,1,54);
    C.set(1,2,114);
    C.set(1,3,108);
    C.set(2,0,40);
    C.set(2,1,58);
    C.set(2,2,110);
    C.set(2,3,102);
    C.set(3,0,16);
    C.set(3,1,26);
    C.set(3,2,46);
    C.set(3,3,42);

    ASSERT_THAT(A * B == C, true);
}

TEST_F(MatrixFeature, TypecastTupleIntoMatrix){
    Tuple vector{1,2,3,1};
    Matrix TrueValue(4,1);
    TrueValue.set(0,0,1);
    TrueValue.set(1,0,2);
    TrueValue.set(2,0,3);
    TrueValue.set(3,0,1);

    Matrix castedTuple{vector};

    ASSERT_THAT(castedTuple == TrueValue, true);
}

TEST_F(MatrixFeature, MultiplyingMatrixByTuple){
    Matrix matrix(4,4);
    matrix.set(0,0,1);
    matrix.set(0,1,2);
    matrix.set(0,2,3);
    matrix.set(0,3,4);
    matrix.set(1,0,2);
    matrix.set(1,1,4);
    matrix.set(1,2,4);
    matrix.set(1,3,2);
    matrix.set(2,0,8);
    matrix.set(2,1,6);
    matrix.set(2,2,4);
    matrix.set(2,3,1);
    matrix.set(3,0,0);
    matrix.set(3,2,0);
    matrix.set(3,1,0);
    matrix.set(3,3,1);

    Tuple tuple{1,2,3,1};

    Tuple productTuple = matrix * tuple;

    Tuple trueValue{18,24,33,1};

    ASSERT_THAT(trueValue == productTuple, true);
}

TEST_F(MatrixFeature, MultiplyingMatrixByIdentityReturnsSameMatrix){
    Matrix matrix(4,4);
    matrix.set(0,0,1);
    matrix.set(0,1,2);
    matrix.set(0,2,3);
    matrix.set(0,3,4);
    matrix.set(1,0,2);
    matrix.set(1,1,4);
    matrix.set(1,2,4);
    matrix.set(1,3,2);
    matrix.set(2,0,8);
    matrix.set(2,1,6);
    matrix.set(2,2,4);
    matrix.set(2,3,1);
    matrix.set(3,0,0);
    matrix.set(3,2,0);
    matrix.set(3,1,0);
    matrix.set(3,3,1);

    Matrix identityMatrix(4, MatrixType::identity);

    Matrix product = matrix * identityMatrix;

    ASSERT_THAT(product == matrix, true);
}

TEST_F(MatrixFeature, MultiplyingTupleByIdentityReturnsSameTuple){
    Tuple tuple{18,24,33,1};
    Matrix identityMatrix(4, MatrixType::identity);
    Tuple product = identityMatrix * tuple;

    ASSERT_THAT(tuple == product, true);
}

TEST_F(MatrixFeature, TransposingMatrix){
    Matrix matrix(4,4);
    matrix.set(0,0,0);
    matrix.set(0,1,9);
    matrix.set(0,2,3);
    matrix.set(0,3,0);
    matrix.set(1,0,9);
    matrix.set(1,1,8);
    matrix.set(1,2,0);
    matrix.set(1,3,8);
    matrix.set(2,0,1);
    matrix.set(2,1,8);
    matrix.set(2,2,5);
    matrix.set(2,3,3);
    matrix.set(3,0,0);
    matrix.set(3,1,0);
    matrix.set(3,2,5);
    matrix.set(3,3,8);

    Matrix trueValue(4,4);
    trueValue.set(0,0,0);
    trueValue.set(0,1,9);
    trueValue.set(0,2,1);
    trueValue.set(0,3,0);
    trueValue.set(1,0,9);
    trueValue.set(1,1,8);
    trueValue.set(1,2,8);
    trueValue.set(1,3,0);
    trueValue.set(2,0,3);
    trueValue.set(2,1,0);
    trueValue.set(2,2,5);
    trueValue.set(2,3,5);
    trueValue.set(3,0,0);
    trueValue.set(3,1,8);
    trueValue.set(3,2,3);
    trueValue.set(3,3,8);

    Matrix transposedMatrix = matrix.transpose();
    ASSERT_THAT(transposedMatrix == trueValue, true);
}

TEST_F(MatrixFeature, TransposingIdentityMatrix){
    Matrix identity(4, MatrixType::identity);
    Matrix identityTransposed = identity.transpose();
    Matrix trueValue(4, MatrixType::identity);

    ASSERT_THAT(identityTransposed == trueValue, true);
}

TEST_F(MatrixFeature, CalculatingDeterminantOfTwoByTwoMatrix){
    Matrix A(2,2);
    A.set(0,0,1);
    A.set(0,1,5);
    A.set(1,0,-3);
    A.set(1,1,2);

    double trueValue{17};

    ASSERT_THAT(A.findDeterminant() == trueValue, true);
}

TEST_F(MatrixFeature, SubmatrixOfThreeByThreeIsTwoByTwoMatrix){
    Matrix matrixA(3,3);
    matrixA.set(0,0,1);
    matrixA.set(0,1,5);
    matrixA.set(0,2,0);
    matrixA.set(1,0,-3);
    matrixA.set(1,1,2);
    matrixA.set(1,2,7);
    matrixA.set(2,0,0);
    matrixA.set(2,1,6);
    matrixA.set(2,2,-3);

    Matrix trueValue(2,2);
    trueValue.set(0,0,-3);
    trueValue.set(0,1,2);
    trueValue.set(1,0,0);
    trueValue.set(1,1,6);

    ASSERT_THAT(matrixA.findSubmatrix(0,2) == trueValue, true);
}

TEST_F(MatrixFeature, SubmatrixOfFourByFourIsThreeByThreeMatrix){
    Matrix matrixA(4,4);
    matrixA.set(0,0,-6);
    matrixA.set(0,1,1);
    matrixA.set(0,2,1);
    matrixA.set(0,3,6);
    matrixA.set(1,0,-8);
    matrixA.set(1,1,5);
    matrixA.set(1,2,8);
    matrixA.set(1,3,6);
    matrixA.set(2,0,-1);
    matrixA.set(2,1,0);
    matrixA.set(2,2,8);
    matrixA.set(2,3,2);
    matrixA.set(3,0,-7);
    matrixA.set(3,1,1);
    matrixA.set(3,2,-1);
    matrixA.set(3,3,1);

    Matrix trueValue(3,3);
    trueValue.set(0,0,-6);
    trueValue.set(0,1,1);
    trueValue.set(0,2,6);
    trueValue.set(1,0,-8);
    trueValue.set(1,1,8);
    trueValue.set(1,2,6);
    trueValue.set(2,0,-7);
    trueValue.set(2,1,-1);
    trueValue.set(2,2,1);

    ASSERT_THAT(matrixA.findSubmatrix(2,1) == trueValue, true);
}

TEST_F(MatrixFeature, CalculatingMinorOfThreeByThreeMatrix){
    Matrix matrixA(3,3);
    matrixA.set(0,0,3);
    matrixA.set(0,1,5);
    matrixA.set(0,2,0);
    matrixA.set(1,0,2);
    matrixA.set(1,1,-1);
    matrixA.set(1,2,-7);
    matrixA.set(2,0,6);
    matrixA.set(2,1,-1);
    matrixA.set(2,2,5);

    double trueValue{25};

    ASSERT_THAT(matrixA.findMinor(1,0) == trueValue, true);
}

TEST_F(MatrixFeature, CalculatingCofactorOfThreeByThreeMatrix){
    Matrix matrixA(3,3);
    matrixA.set(0,0,3);
    matrixA.set(0,1,5);
    matrixA.set(0,2,0);
    matrixA.set(1,0,2);
    matrixA.set(1,1,-1);
    matrixA.set(1,2,-7);
    matrixA.set(2,0,6);
    matrixA.set(2,1,-1);
    matrixA.set(2,2,5);

    ASSERT_THAT(matrixA.findMinor(0,0) == -12, true);
    ASSERT_THAT(matrixA.findCofactor(0,0) == -12, true);
    ASSERT_THAT(matrixA.findMinor(1,0) == 25, true);
    ASSERT_THAT(matrixA.findCofactor(1,0) == -25, true);
}

TEST_F(MatrixFeature, CalculatingDeterminantOfThreeByThreeMatrix){
    Matrix matrix(3,3);
    matrix.set(0,0,1);
    matrix.set(0,1,2);
    matrix.set(0,2,6);
    matrix.set(1,0,-5);
    matrix.set(1,1,8);
    matrix.set(1,2,-4);
    matrix.set(2,0,2);
    matrix.set(2,1,6);
    matrix.set(2,2,4);

    ASSERT_THAT(matrix.findCofactor(0,0), Eq(56));
    ASSERT_THAT(matrix.findCofactor(0,1), Eq(12));
    ASSERT_THAT(matrix.findCofactor(0,2), Eq(-46));
    ASSERT_THAT(matrix.findDeterminant(), Eq(-196));
}

TEST_F(MatrixFeature, CalculatingDeterminantOfFourByFourMatrix){
    Matrix matrix(4,4);
    matrix.set(0,0,-2);
    matrix.set(0,1,-8);
    matrix.set(0,2,3);
    matrix.set(0,3,5);
    matrix.set(1,0,-3);
    matrix.set(1,1,1);
    matrix.set(1,2,7);
    matrix.set(1,3,3);
    matrix.set(2,0,1);
    matrix.set(2,1,2);
    matrix.set(2,2,-9);
    matrix.set(2,3,6);
    matrix.set(3,0,-6);
    matrix.set(3,1,7);
    matrix.set(3,2,7);
    matrix.set(3,3,-9);

    ASSERT_THAT(matrix.findCofactor(0,0), Eq(690));
    ASSERT_THAT(matrix.findCofactor(0,1), Eq(447));
    ASSERT_THAT(matrix.findCofactor(0,2), Eq(210));
    ASSERT_THAT(matrix.findCofactor(0,3), Eq(51));
    ASSERT_THAT(matrix.findDeterminant(), Eq(-4071));
}

TEST_F(MatrixFeature, CalculatingInverseOfMatrix){
    Matrix matrix(4,4);
    matrix.set(0,0,-5);
    matrix.set(0,1,2);
    matrix.set(0,2,6);
    matrix.set(0,3,-8);
    matrix.set(1,0,1);
    matrix.set(1,1,-5);
    matrix.set(1,2,1);
    matrix.set(1,3,8);
    matrix.set(2,0,7);
    matrix.set(2,1,7);
    matrix.set(2,2,-6);
    matrix.set(2,3,-7);
    matrix.set(3,0,1);
    matrix.set(3,1,-3);
    matrix.set(3,2,7);
    matrix.set(3,3,4);

    Matrix inverse(4,4);
    inverse.set(0,0,0.21805);
    inverse.set(0,1,0.45113);
    inverse.set(0,2,0.24060);
    inverse.set(0,3,-0.04511);
    inverse.set(1,0,-0.80827);
    inverse.set(1,1,-1.45677);
    inverse.set(1,2,-0.44361);
    inverse.set(1,3,0.52068);
    inverse.set(2,0,-0.07895);
    inverse.set(2,1,-0.22368);
    inverse.set(2,2,-0.05263);
    inverse.set(2,3,0.19737);
    inverse.set(3,0,-0.52256);
    inverse.set(3,1,-0.81391);
    inverse.set(3,2,-0.30075);
    inverse.set(3,3,0.30639);

    Matrix invertedMatrix = matrix.invert();

    ASSERT_THAT(matrix.findDeterminant(), Eq(532));
    ASSERT_THAT(matrix.findCofactor(2,3), Eq(-160));
    ASSERT_THAT(matrix.findCofactor(3,2), Eq(105));
    ASSERT_THAT(inverse == invertedMatrix, true);
}

TEST_F(MatrixFeature, CalculatingInverseOfSecondMatrix){
    Matrix matrix(4,4);
    matrix.set(0,0,8);
    matrix.set(0,1,-5);
    matrix.set(0,2,9);
    matrix.set(0,3,2);
    matrix.set(1,0,7);
    matrix.set(1,1,5);
    matrix.set(1,2,6);
    matrix.set(1,3,1);
    matrix.set(2,0,-6);
    matrix.set(2,1,0);
    matrix.set(2,2,9);
    matrix.set(2,3,6);
    matrix.set(3,0,-3);
    matrix.set(3,1,0);
    matrix.set(3,2,-9);
    matrix.set(3,3,-4);

    Matrix inverse(4,4);
    inverse.set(0,0,-0.15385);
    inverse.set(0,1,-0.15385);
    inverse.set(0,2,-0.28205);
    inverse.set(0,3,-0.53846);
    inverse.set(1,0,-0.07692);
    inverse.set(1,1,0.12308);
    inverse.set(1,2,0.02564);
    inverse.set(1,3,0.03077);
    inverse.set(2,0,0.35897);
    inverse.set(2,1,0.35897);
    inverse.set(2,2,0.43590);
    inverse.set(2,3,0.92308);
    inverse.set(3,0,-0.69231);
    inverse.set(3,1,-0.69231);
    inverse.set(3,2,-0.76923);
    inverse.set(3,3,-1.92308);

    Matrix invertedMatrix = matrix.invert();

    ASSERT_THAT(inverse == invertedMatrix, true);
}

TEST_F(MatrixFeature, CalculatingInverseOfThirdMatrix){
    Matrix matrix(4,4);
    matrix.set(0,0,9);
    matrix.set(0,1,3);
    matrix.set(0,2,0);
    matrix.set(0,3,9);
    matrix.set(1,0,-5);
    matrix.set(1,1,-2);
    matrix.set(1,2,-6);
    matrix.set(1,3,-3);
    matrix.set(2,0,-4);
    matrix.set(2,1,9);
    matrix.set(2,2,6);
    matrix.set(2,3,4);
    matrix.set(3,0,-7);
    matrix.set(3,1,6);
    matrix.set(3,2,6);
    matrix.set(3,3,2);

    Matrix inverse(4,4);
    inverse.set(0,0,-0.04074);
    inverse.set(0,1,-0.07778);
    inverse.set(0,2,0.14444);
    inverse.set(0,3,-0.22222);
    inverse.set(1,0,-0.07778);
    inverse.set(1,1,0.03333);
    inverse.set(1,2,0.36667);
    inverse.set(1,3,-0.33333);
    inverse.set(2,0,-0.02901);
    inverse.set(2,1,-0.14630);
    inverse.set(2,2,-0.10926);
    inverse.set(2,3,0.12963);
    inverse.set(3,0,0.17778);
    inverse.set(3,1,0.06667);
    inverse.set(3,2,-0.26667);
    inverse.set(3,3,0.33333);

    Matrix invertedMatrix = matrix.invert();

    ASSERT_THAT(inverse == invertedMatrix, true);
}

TEST_F(MatrixFeature, MultiplyingProductByItsInverse){
    Matrix A(4,4);
    A.set(0,0,3);
    A.set(0,1,-9);
    A.set(0,2,7);
    A.set(0,3,3);
    A.set(1,0,3);
    A.set(1,1,-8);
    A.set(1,2,2);
    A.set(1,3,-9);
    A.set(2,0,-4);
    A.set(2,1,4);
    A.set(2,2,4);
    A.set(2,3,1);
    A.set(3,0,-6);
    A.set(3,1,5);
    A.set(3,2,-1);
    A.set(3,3,1);

    Matrix B(4,4);
    B.set(0,0,8);
    B.set(0,1,2);
    B.set(0,2,2);
    B.set(0,3,2);
    B.set(1,0,3);
    B.set(1,1,-1);
    B.set(1,2,7);
    B.set(1,3,0);
    B.set(2,0,7);
    B.set(2,1,0);
    B.set(2,2,5);
    B.set(2,3,4);
    B.set(3,0,6);
    B.set(3,1,-2);
    B.set(3,2,0);
    B.set(3,3,5);

    Matrix C = A * B;
//    A.print2screen();

    ASSERT_THAT(C * B.invert() == A, true);
}
