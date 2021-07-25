#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <cmath>

class Matrix {
private:
    int **mat;
    int** reduceMatrix(int** mat, int n, int x, int y);
    int calculateRecursiveDeterminant(int** mat, int n);
public:
    Matrix(int n);
    Matrix(int r, int c);
    void setCell(int i, int j, int x);
    int calculateRecursiveDeterminant(int n);


};

#endif /* MATRIX_H */
