#include <iostream>
#include <chrono>
#include <omp.h>

using namespace std;

const int size = 1000;

float arraySum (float array[], double * execTime) {
    float aux = 0;

    chrono::steady_clock::time_point start = chrono::steady_clock::now();

    #pragma omp parallel for
    for (int i = 0; i < size; i++)
        aux += array[i];

    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    chrono::duration<double> executionTIme = chrono::duration_cast<chrono::duration<double>>(end - start);
    *execTime = executionTIme.count();

    return aux;
};

int arraySum (int array[], double * execTime) {
    int aux = 0;

    chrono::steady_clock::time_point start = chrono::steady_clock::now();

    #pragma omp parallel for
    for (int i = 0; i < size; i++)
        aux += array[i];

    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    chrono::duration<double> executionTIme = chrono::duration_cast<chrono::duration<double>>(end - start);
    *execTime = executionTIme.count();

    return aux;
};

void fillFloatArray (float array[]) {
    for (int i = 0; i < size; i++)
        array[i] = i;
};

void fillIntegerArray (int array[]) {
    for (int i = 0; i < size; i++)
        array[i] = i;
};

int main ()
{
    int integerResult;
    float floatResult;
    double execTimeX, execTimeY;

    int arrayInt[size];
    fillIntegerArray(arrayInt);
    integerResult = arraySum(arrayInt, &execTimeX);
    cout << "The int exec time was " << execTimeX << " and the end result is " << integerResult << endl << endl;

    float arrayFloat[size];
    fillFloatArray(arrayFloat);
    floatResult = arraySum(arrayFloat, &execTimeY);
    cout << "The float exec time was " << execTimeY << " and the end result is " << floatResult << endl << endl;

    return 0;
}