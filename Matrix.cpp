#include "Matrix.h"

Matrix::Matrix(int n){
    this->r = n;
    this->c = n;
    mat = new int*[n];
    for(int i=0;i<n;i++){
        mat[i] = new int[n];
    }
}


void Matrix::setCell(int i, int j, int x){
    this->mat[i][j]=x;
}



int** Matrix::reduceMatrix(int** mat, int n, int x, int y){
    int** newMat = new int*[n-1];
    for(int i=0;i<(n-1);i++){
        newMat[i] = new int[n-1];
    }
    int nj=0,ni=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i!=x && j!=y){
                newMat[ni][nj]=mat[i][j];
                nj++;
            }
        }
        if(i!=x){
            ni++;
        }
        nj=0;
    }
    return newMat;
}

int Matrix::calculateRecursiveDeterminant(int** mat, int n){
    if(n==1){
        return mat[0][0];
    } else {
        int sum=0;
        for(int j=0;j<n;j++){
            sum+=pow(-1,j)*mat[0][j]*calculateRecursiveDeterminant(reduceMatrix(mat,n,0,j),n-1);
        }
        return sum;
    }
}

int Matrix::calculateRecursiveDeterminant(){
    if(r==c)
        return calculateRecursiveDeterminant(mat,r);
    else
        return 0;
}



