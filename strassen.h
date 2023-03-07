#ifndef STRASSEN_H
#define STRASSEN_H

void naiveApproach(int**, int**, int**, int );
void divideAndConquer(int**, int**, int**, int);
void splitIntoFour(int**, int**, int**, int**, int**, int);
void printMatrix(int**, int);
//void printMatrix(ofstream, int**, int);
void matrixAdd(int**, int**, int**, int);
void matrixSubtract(int**, int**, int**, int);
void matrixCombine(int**, int**, int**, int**, int**, int);
void strassen(int**, int**, int**, int);

#endif
