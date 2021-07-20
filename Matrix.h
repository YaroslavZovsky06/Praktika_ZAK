#ifndef MATRIX_H
#define MATRIX_H
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <QDebug>

class Matrix {
private:
    int r;
    int c;
    int **mat;
    int** reduceMatrix(int** mat, int n, int x, int y);
    int calculateRecursiveDeterminant(int** mat, int n);
public:
    Matrix(int n);
    Matrix(int r, int c);
    void setCell(int i, int j, int x);
    int calculateRecursiveDeterminant();


};

#endif /* MATRIX_H */
