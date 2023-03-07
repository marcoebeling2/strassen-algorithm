#include <iostream>
#include <cmath>
#include <iomanip>
#include <stdio.h>
#include <cstring>
#include <fstream>
#include <time.h>
//#include <./stressen.h>


using namespace std;

void naiveApproach(int** outM, int** m1, int** m2, int size);
void divideAndConquer(int** outM, int** m1, int** m2, int size);
void splitIntoFour(int** m1, int** a, int**b, int** c, int** d, int size);
void printMatrix(int** m, int size);
void printMatrix(ofstream &ofStr, int** m, int size);
void matrixAdd(int** outM, int** m1, int** m2, int size);
void matrixSubtract(int** outM, int** m1, int** m2, int size);
void matrixCombine(int** outM, int** C11, int** C12, int** C21, int** C22, int inSize);
void strassen(int** outM, int** m1, int** m2, int size);


int main(){

    // read in data from input.txt
    ifstream ifStr;
    ifStr.open("input.txt");

    // get the first int from the first line
    int n;
    ifStr >> n;
    // get line to go to next line
    string temp;
    getline(ifStr, temp);

    // if n is not a 2^n integer, make it so
    int size = 2;
    while ((n > size) && (n != size)){
        size = size * 2;
    }
    



    // initialize arrays to use
    int** m1 = new int*[size];
    int** m2 = new int*[size];
    int** naiveM = new int*[size];
    int** divideM = new int*[size];
    int** strassenM = new int*[size];
    // Using system time as a seed value
    srand((unsigned) time(NULL));
    for (int i = 0; i < size; i++){
        m1[i] = new int[size];
        m2[i] = new int[size];
        naiveM[i] = new int[size];
        divideM[i] = new int[size];
        strassenM[i] = new int[size];
        // fill m1 and m2
        for (int j =0; j < size; j++){
            m1[i][j] = (rand() % 4) + 1;
            m2[i][j] = (rand() % 4) + 1;
            naiveM[i][j] = 0;
            divideM[i][j] = 0;
        }
    }

    // use string streams to get the data
    string temp1;
    for (int i = 0; i < size; i++){
        // only fill in for data for i and h <= n
        if (i < n){
            getline(ifStr, temp1);
            stringstream ss1(temp1);
            for (int j = 0; j < size; j++){
                if (j < n){
                    ss1 >> m1[i][j];
                }
                else {
                    m1[i][j] = 0;
                }
            }
        }
        else {
            for (int j = 0; j < size; j++){
                m1[i][j] = 0;
            }
        }
    }
    // now m2
    // use string streams to get the data
    string temp2;
    for (int i = 0; i < size; i++){
        // only fill in for data for i and h <= n
        if (i < n){
            getline(ifStr, temp2);
            stringstream ss2(temp2);
            for (int j = 0; j < size; j++){
                if (j < n){
                    ss2 >> m2[i][j];
                }
                else {
                    m2[i][j] = 0;
                }
            }
        }
        else {
            for (int j = 0; j < size; j++){
                m2[i][j] = 0;
            }
        }
    }


    // close ifStr
    ifStr.close();

    // create time objects
    time_t s1, e1, s2, e2;

    // compute through naive approach and print
    naiveApproach(naiveM, m1, m2, size);

    // delete naiveM
    for (int i = 0; i < size; i++){
        delete [] naiveM[i];
    }
    delete [] naiveM;

    // compute through divide and conquer and print
        // also calculate time
    s1 = clock();
    divideAndConquer(divideM, m1, m2, size);
    e1 = clock();
    // make ofstream to print to
    ofstream ofStr1;
    ofStr1.open("output_m1.txt");
    printMatrix(ofStr1, divideM, n);
    // close ofstr1
    ofStr1.close();

    // delete divideM
    for (int i = 0; i < size; i++){
        delete [] divideM[i];
    }
    delete [] divideM;

    // compute strassen
    s2 = clock();
    strassen(strassenM, m1, m2, size);
    e2 = clock();
    // make ofStr to print output
    ofstream ofStr2;
    ofStr1.open("output_m2.txt");
    printMatrix(ofStr1, strassenM, n);
    // close ofstr1
    ofStr2.close();

    // delete strassenM
    for (int i = 0; i < size; i++){
        delete [] strassenM[i];
    }
    delete [] strassenM;

    // delete m1 and m2
    for (int i = 0; i < size; i++){
        delete [] m1[i];
        delete [] m2[i];
    }
    delete [] m1;
    delete [] m2;

    // create an ofstream for the time
    ofstream ofStr3;
    ofStr3.open("output_q3.txt");
    ofStr3 << e1 - s1 << " " << e2 - s2 << endl;




    return 0;
}
