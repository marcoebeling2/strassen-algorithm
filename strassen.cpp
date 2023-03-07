#include <iostream>
#include <cmath>
#include <iomanip>
#include <stdio.h>
#include <cstring>
#include <fstream>
#include <time.h>
#include "strassen.h"


using namespace std;

void printMatrix(ofstream &ofStr, int** m, int size);

void naiveApproach(int** outM, int** m1, int** m2, int size){
    // assume a square matrix
    // assume out array is filled with zeros
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            outM[i][j] = 0; // reset the matrix value
            for (int k = 0; k < size; k++){
                outM[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
}

void printMatrix(int** m, int size){
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            cout << setw(4) << m[i][j] << " ";
        }
        cout << endl;
    }
}

void printMatrix(ofstream &ofStr, int** m, int size){
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            ofStr << setw(4) << m[i][j] << " ";
        }
        ofStr << endl;
    }
}

void splitIntoFour(int** m1, int** a, int** b, int** c, int** d, int size){
    // use a for loop to allocate each 
    for (int i = 0; i < size/2; i++){
        a[i] = new int[size/2];
        b[i] = new int[size/2];
        c[i] = new int[size/2];
        d[i] = new int[size/2];
        for (int j = 0; j < size/2; j++){
            a[i][j] = m1[i][j];
            b[i][j] = m1[i][j + (size/2)];
            c[i][j] = m1[i + (size/2)][j];
            d[i][j] = m1[i + (size/2)][j + (size/2)];
        }
    }
}

void matrixAdd(int** outM, int** m1, int** m2, int size){
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            outM[i][j] = m1[i][j] + m2[i][j];
        }
    }
}

void matrixCombine(int** outM, int** C11, int** C12, int** C21, int** C22, int inSize){
    // use for loops to assign the four matrices
    for (int i = 0; i < inSize; i++){
        for (int j = 0; j < inSize; j++){
            outM[i][j] = C11[i][j];
            outM[i][j + inSize] = C12[i][j];
            outM[i + inSize][j] = C21[i][j];
            outM[i + inSize][j + inSize] = C22[i][j];
        }
    }
}

void divideAndConquer(int** outM, int** m1, int** m2, int size){
    // base case
    if (size <= 2){
        // probably have to deallocate here
        naiveApproach(outM, m1, m2, size);
        return;
    }
    // split each matrix into 4 even size/2 parts
    // make 3d array to hold each 2d array
    // a, b, c, d
    int*** abcd = new int**[4];
    // e, f, g, h
    int*** efgh = new int**[4];
    // allocate memory
    for (int i = 0; i < 4; i++){
        abcd[i] = new int*[size/2];
        efgh[i] = new int*[size/2];
    }
    // split each matrix
    splitIntoFour(m1, abcd[0], abcd[1], abcd[2], abcd[3], size);
    splitIntoFour(m2, efgh[0], efgh[1], efgh[2], efgh[3], size);

    // make another 3d matrix to hold ae, bg, ... , dh
    // ae, bg, af, bh, ce, dg, cf, dh
    int*** aeToDH = new int**[8];
    // allocate memory
    for (int i = 0; i < 8; i++){
        aeToDH[i] = new int*[size/2];
        for (int j = 0; j < size/2; j++){
            aeToDH[i][j] = new int[size/2];
        }
    }
    // calculate each recursively
    divideAndConquer(aeToDH[0], abcd[0], efgh[0], size/2);
    //cout << "ae:" << endl;
    //printMatrix(aeToDH[0], size/2);
    divideAndConquer(aeToDH[1], abcd[1], efgh[2], size/2);
    divideAndConquer(aeToDH[2], abcd[0], efgh[1], size/2);
    divideAndConquer(aeToDH[3], abcd[1], efgh[3], size/2);
    divideAndConquer(aeToDH[4], abcd[2], efgh[0], size/2);
    divideAndConquer(aeToDH[5], abcd[3], efgh[2], size/2);
    divideAndConquer(aeToDH[6], abcd[2], efgh[1], size/2);
    divideAndConquer(aeToDH[7], abcd[3], efgh[3], size/2);


    // delete abcd efgh
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < size/2; j++){
            delete [] abcd[i][j];
            delete [] efgh[i][j];
        }
        delete [] abcd[i];
        delete [] efgh[i];
    }
    delete [] abcd;
    delete [] efgh;

    // add the four sub squares for aeToDH
    // use a 3d Matrix to hold the 2d matrix
    int*** c11c12c21c22 = new int**[4];
    for (int i = 0; i < 4; i++){
        c11c12c21c22[i] = new int*[size/2];
        for (int j = 0; j < size/2; j++){
            c11c12c21c22[i][j] = new int[size/2];
        }
    }
    // use matrix addition to get the four sub matrices
    matrixAdd(c11c12c21c22[0], aeToDH[0], aeToDH[1], size/2);
    matrixAdd(c11c12c21c22[1], aeToDH[2], aeToDH[3], size/2);
    matrixAdd(c11c12c21c22[2], aeToDH[4], aeToDH[5], size/2);
    matrixAdd(c11c12c21c22[3], aeToDH[6], aeToDH[7], size/2);

    // delete aeToDH
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < size/2; j++){
            delete [] aeToDH[i][j];
        }
        delete [] aeToDH[i];
    }
    delete [] aeToDH;

    // combine the four matrices to produce the output matrix
    matrixCombine(outM, c11c12c21c22[0], c11c12c21c22[1], c11c12c21c22[2], c11c12c21c22[3], size/2); 

    // delete c11c12c21c22
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < size/2; j++){
            delete [] c11c12c21c22[i][j];
        }
        delete [] c11c12c21c22[i];
    }
    delete [] c11c12c21c22;

}

void strassen(int** outM, int** m1, int** m2, int size){
    // base case
    if (size <= 2){
        // probably have to deallocate here
        naiveApproach(outM, m1, m2, size);
        return;
    }
    // split each matrix into 4 even size/2 parts
    // make 3d array to hold each 2d array
    // a, b, c, d
    int*** abcd = new int**[4];
    // e, f, g, h
    int*** efgh = new int**[4];
    // allocate memory
    for (int i = 0; i < 4; i++){
        abcd[i] = new int*[size/2];
        efgh[i] = new int*[size/2];
    }
    // split each matrix
    splitIntoFour(m1, abcd[0], abcd[1], abcd[2], abcd[3], size);
    splitIntoFour(m2, efgh[0], efgh[1], efgh[2], efgh[3], size);
         

    // make another 3d matrix to hold p1, p2, p3, p4, p5, p6, p7
    int*** p = new int**[7];
    // allocate memory
    for (int i = 0; i < 7; i++){
        p[i] = new int*[size/2];
        for (int j = 0; j < size/2; j++){
            p[i][j] = new int[size/2];
        }
    }
    // create sub arrays
    int** aPlusD = new int*[size/2];
    int** ePlusH = new int*[size/2];
    int** gMinusE = new int*[size/2];
    int** aPlusB = new int*[size/2];
    int** bMinusD = new int*[size/2];
    int** gPlusH = new int*[size/2];
    int** fMinusH = new int*[size/2];
    int** cPlusD = new int*[size/2];
    int** aMinusC = new int*[size/2];
    int** ePlusF = new int*[size/2];
    // populate each subarray
    for (int i = 0; i < size/2; i++){
        aPlusD[i] = new int[size/2];
        ePlusH[i] = new int[size/2];
        gMinusE[i] = new int[size/2];
        aPlusB[i] = new int[size/2];
        bMinusD[i] = new int[size/2];
        gPlusH[i] = new int[size/2];
        fMinusH[i] = new int[size/2];
        cPlusD[i] = new int[size/2];
        aMinusC[i] = new int[size/2];
        ePlusF[i] = new int[size/2];
    }
    // complete necessary operations
    matrixAdd(aPlusD, abcd[0], abcd[3], size/2);
    matrixAdd(ePlusH, efgh[0], efgh[3], size/2);
    matrixSubtract(gMinusE, efgh[2], efgh[0], size/2);
    matrixAdd(aPlusB, abcd[0], abcd[1], size/2);
    matrixSubtract(bMinusD, abcd[1], abcd[3], size/2);
    matrixAdd(gPlusH, efgh[2], efgh[3], size/2);
    matrixSubtract(fMinusH, efgh[1], efgh[3], size/2);
    matrixAdd(cPlusD, abcd[2], abcd[3], size/2);
    matrixSubtract(aMinusC, abcd[0], abcd[2], size/2);
    matrixAdd(ePlusF, efgh[0], efgh[1], size/2);



    // calculate each recursively
    strassen(p[0], aPlusD, ePlusH, size/2);
    strassen(p[1], abcd[3], gMinusE, size/2);
    strassen(p[2], aPlusB, efgh[3], size/2);
    strassen(p[3], bMinusD, gPlusH, size/2);
    strassen(p[4], abcd[0], fMinusH, size/2);
    strassen(p[5], cPlusD, efgh[0], size/2);
    strassen(p[6], aMinusC, ePlusF, size/2);


    // delete abcd efgh
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < size/2; j++){
            delete [] abcd[i][j];
            delete [] efgh[i][j];
        }
        delete [] abcd[i];
        delete [] efgh[i];
    }
    delete [] abcd;
    delete [] efgh;

    // delete computed matrices
    for (int i = 0; i < size/2; i++){
        delete [] aPlusD[i];
        delete [] ePlusH[i];
        delete [] gMinusE[i];
        delete [] aPlusB[i];
        delete [] bMinusD[i];
        delete [] gPlusH[i];
        delete [] fMinusH[i];
        delete [] cPlusD[i];
        delete [] aMinusC[i];
        delete [] ePlusF[i];
    }
    delete [] aPlusD;
    delete [] ePlusH;
    delete [] gMinusE;
    delete [] aPlusB;
    delete [] bMinusD;
    delete [] gPlusH;
    delete [] fMinusH;
    delete [] cPlusD;
    delete [] aMinusC;
    delete [] ePlusF;
    

    // add the four sub squares for aeToDH
    // use a 3d Matrix to hold the 2d matrix
    int*** c11c12c21c22 = new int**[4];
    for (int i = 0; i < 4; i++){
        c11c12c21c22[i] = new int*[size/2];
        for (int j = 0; j < size/2; j++){
            c11c12c21c22[i][j] = new int[size/2];
        }
    }

    // use matrix addition and subtraction to get the four sub matrices
    matrixAdd(c11c12c21c22[0], p[0], p[1], size/2);
    matrixSubtract(c11c12c21c22[0], c11c12c21c22[0], p[2], size/2);
    matrixAdd(c11c12c21c22[0], c11c12c21c22[0], p[3], size/2);
    matrixAdd(c11c12c21c22[1], p[4], p[2], size/2);
    matrixAdd(c11c12c21c22[2], p[5], p[1], size/2);
    matrixAdd(c11c12c21c22[3], p[4], p[0], size/2);
    matrixSubtract(c11c12c21c22[3], c11c12c21c22[3], p[5], size/2);
    matrixSubtract(c11c12c21c22[3], c11c12c21c22[3], p[6], size/2);

    // delete p
    for (int i = 0; i < 7; i++){
        for (int j = 0; j < size/2; j++){
            delete [] p[i][j];
        }
        delete [] p[i];
    }
    delete [] p;

    // combine the four matrices to produce the output matrix
    matrixCombine(outM, c11c12c21c22[0], c11c12c21c22[1], c11c12c21c22[2], c11c12c21c22[3], size/2); 

    // delete c11c12c21c22
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < size/2; j++){
            delete [] c11c12c21c22[i][j];
        }
        delete [] c11c12c21c22[i];
    }
    delete [] c11c12c21c22;
}

void matrixSubtract(int** outM, int** m1, int** m2, int size){
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            outM[i][j] = m1[i][j] - m2[i][j];
        }
    }
}