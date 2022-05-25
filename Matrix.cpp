#include "Matrix.h"
#include "Tuple.h"

Matrix::Matrix(int n_rows, int n_columns) : rowCount{n_rows}, columnCount{n_columns}{
    int arraySize = rowCount * columnCount;
    flattenedArray = new double[arraySize];
    for (int i = 0; i < arraySize; i++){
        flattenedArray[i] = 0;
    }
    setNumberOfElements();
}

Matrix::Matrix(const Tuple& tuple) : rowCount{4}, columnCount{1} {
    setNumberOfElements();
    int arraySize = 4;
    flattenedArray = new double[arraySize];
    flattenedArray[0] = tuple.getXValue();
    flattenedArray[1] = tuple.getYValue();
    flattenedArray[2] = tuple.getZValue();
    flattenedArray[3] = tuple.getWValue();
}

Matrix::Matrix(int matrixSize, MatrixType type) : rowCount{matrixSize}, columnCount{matrixSize}{
    int arraySize = rowCount * columnCount;
    flattenedArray = new double[arraySize];
    for (int i = 0; i < arraySize; i++){
        flattenedArray[i] = 0;
    }
    switch (type) {
    case MatrixType::identity: {
        for (int i = 0; i < arraySize; i = i + matrixSize + 1){
            flattenedArray[i] = 1.0;
        }
    } break;
    }
    setNumberOfElements();
}

Matrix::~Matrix(){
    delete [] flattenedArray;
}

void Matrix::set(int row, int column, double value){
    flattenedArray[row * columnCount + column] = value;
}

double Matrix::get(int row, int column) const{
    double value = flattenedArray[row * columnCount + column];
    return value;
}

void Matrix::setNumberOfElements(){
    numberOfElements = rowCount * columnCount;
}

bool operator== (const Matrix& matrixA, const Matrix& matrixB){
        using namespace util;
        if (matrixA.rowCount == matrixB.rowCount && matrixA.columnCount == matrixB.columnCount){
            for (int i = 0; i < matrixA.numberOfElements; i++){
                if (!equals(matrixA.flattenedArray[i], matrixB.flattenedArray[i])) return false;
            }
            return true;
        }
        else return false;
    }

Matrix operator*(const Matrix& matrixA, const Matrix& matrixB){
        Matrix product(matrixA.rowCount, matrixB.columnCount);
        double cellValue{};
        for (int i = 0; i < product.rowCount; i++){
            for (int j = 0; j < product.columnCount; j++){
                cellValue = matrixA.get(i,0) * matrixB.get(0,j) +
                            matrixA.get(i,1) * matrixB.get(1,j) +
                            matrixA.get(i,2) * matrixB.get(2,j) +
                            matrixA.get(i,3) * matrixB.get(3,j);
                product.set(i,j,cellValue);
            }
        }
        return product;
    }

Matrix Matrix::transpose() const{
    Matrix transposed(this->columnCount, this->rowCount);
    for (int i = 0; i < transposed.rowCount; i++){
        for (int j = 0; j < transposed.columnCount; j++){
            transposed.set(i,j, this->get(j,i));
        }
    }
    return transposed;
}

double Matrix::findDeterminant() const{
    double determinant{};
    if (this->rowCount == 2 && this->columnCount == 2){
        determinant = this->get(0,0) * this->get(1,1) - this->get(0,1) * this->get(1,0);
    }
    else{
        for (int j = 0; j < this->columnCount; j++){
            determinant = determinant + this->get(0,j) * this->findCofactor(0,j);
        }
    }
    return determinant;
}

Matrix Matrix::findSubmatrix(int rowNumber, int columnNumber) const{
    Matrix submatrix(this->rowCount - 1, this->columnCount - 1);
    double* flattenedArrayPointer = submatrix.flattenedArray;
    for (int i = 0; i < this->rowCount; i++){
        if (i == rowNumber) continue;
        for (int j = 0; j < this->columnCount; j++){
            if (j == columnNumber) continue;
            *flattenedArrayPointer = this->get(i,j);
            flattenedArrayPointer++;
        }
    }
    return submatrix;
}

double Matrix::findMinor(int rowNumber, int columnNumber) const{
    Matrix submatrix = this->findSubmatrix(rowNumber, columnNumber);
    return submatrix.findDeterminant();
}

double Matrix::findCofactor(int rowNumber, int columnNumber) const{
    double minor = this->findMinor(rowNumber, columnNumber);
    if (((rowNumber + columnNumber) & 1) == 0) return minor;
    else return minor * -1;
}

Matrix Matrix::invert() const{
    double determinant = this->findDeterminant();
    assert(determinant != 0);       //better use catch-try instead.
    Matrix inverse(this->rowCount, this->columnCount);
    double cofactor{};
    for (int i = 0; i < this->rowCount; i++){
        for (int j = 0; j < this->columnCount; j++){
            cofactor = this->findCofactor(i,j);
            inverse.set(j,i, cofactor / determinant);
        }
    }
    return inverse;
}

void Matrix::print2screen() const{
    using namespace std;
    for (int i = 0; i < this->rowCount; i++){
        for (int j = 0; j < this->columnCount; j++){
            cout << "| " << this->get(i,j) << " ";
        }
        if (i != this->rowCount) cout << "|" << endl;
    }
}
