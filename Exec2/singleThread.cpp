#include <iostream>
#include <chrono>

using namespace std;

const int size = 1000;




float arrayFloatSum (float array[], double * executionTIme) {
    float aux = 0;

    chrono::steady_clock::time_point start = chrono::steady_clock::now();

    for (int i = 0; i < size; i++)
        aux += array[i];

    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    chrono::duration<double> execTime = chrono::duration_cast<chrono::duration<double>>(end - start);
    *executionTIme = execTime.count();

    return aux;
};

int arrayIntegerSum (int array[], double * executionTIme) {
    int aux = 0;

    chrono::steady_clock::time_point start = chrono::steady_clock::now();

    for (int i = 0; i < size; i++)
        aux += array[i];

    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    chrono::duration<double> execTime = chrono::duration_cast<chrono::duration<double>>(end - start);
    *executionTIme = execTime.count();

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
    double executionTimeX, executionTimeY;

    int arrayInt[size];
    fillIntegerArray(arrayInt);
    integerResult = arrayIntegerSum(arrayInt, &executionTimeX);
    cout << "Integer execution time was " << executionTimeX << " and the end result was " << integerResult << endl << endl;

    float arrayFloat[size];
    fillFloatArray(arrayFloat);
    floatResult = arrayFloatSum(arrayFloat, &executionTimeY);
    cout << "Float execution time was " << executionTimeY << " and the end result was " << floatResult << endl << endl;

    return 0;
}