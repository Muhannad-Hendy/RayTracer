#ifndef MATRIX_H
#define MATRIX_H

#include "Utilities.h"
//#include "Tuple.h"
#include <cassert>
#include <iostream>

class Tuple;

enum class MatrixType{
    identity
};

class Matrix
{
public:
    Matrix(int n_rows, int n_columns);

    Matrix(const Tuple& tuple);

    Matrix(int matrixSize, MatrixType type);

    ~Matrix();

    void set(int row, int column, double value);

    double get(int row, int column) const;

   void setNumberOfElements();

    friend bool operator== (const Matrix& matrixA, const Matrix& matrixB);

    friend Matrix operator*(const Matrix& matrixA, const Matrix& matrixB);

    Matrix transpose() const;

    double findDeterminant() const;

    Matrix findSubmatrix(int rowNumber, int columnNumber) const;

    double findMinor(int rowNumber, int columnNumber) const;

    double findCofactor(int rowNumber, int columnNumber) const;

    Matrix invert() const;

    void print2screen() const;

private:
    int rowCount{};
    int columnCount{};
    int numberOfElements{};
    double* flattenedArray;
};

#endif // MATRIX_H
