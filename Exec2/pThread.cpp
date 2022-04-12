#include <iostream>
#include <chrono>
#include <pthread.h>

using namespace std;

int execType = 1; // 0 = FLOAT -- 1 == INTEGER

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

const int threadQty = 4;
const int size = 1000;

int slice = 0; // Aux

int arrayInt[size], intSum[threadQty], integerResult;
float arrayFloat[size], floatSum[threadQty], floatResult;
double executionTime;

void * sumIntArray (void * arg) {
    pthread_mutex_lock(&lock);
    int arraySlice = slice;
    slice++;
    pthread_mutex_unlock(&lock);
  
    for (int i = arraySlice * (size / threadQty); i < (arraySlice + 1) * (size / threadQty); i++)
        intSum[arraySlice] += arrayInt[i];

    return nullptr;
};

void * sumFloatArray (void * arg) {
    pthread_mutex_lock(&lock);
    int arraySlice = slice;
    slice++;
    pthread_mutex_unlock(&lock);
  
    for (int i = arraySlice * (size / threadQty); i < (arraySlice + 1) * (size / threadQty); i++)
        floatSum[arraySlice] += arrayFloat[i];

    return nullptr;
};

void fillIntegerArray (int array[]) {
    for (int i = 0; i < size; i++)
        array[i] = i;
};

void fillFloatArray (float array[]) {
    for (int i = 0; i < size; i++)
        array[i] = i;
};

int main ()
{
    chrono::duration<double> execTime;
    chrono::steady_clock::time_point start;
    chrono::steady_clock::time_point end;

    fillIntegerArray(arrayInt);
    fillFloatArray(arrayFloat);

    pthread_t threads[threadQty];

    if (execType == 0) {
        start = chrono::steady_clock::now();

        for (int i = 0; i < threadQty; i++)
            pthread_create(&threads[i], NULL, sumFloatArray, (void*)NULL);

        for (int i = 0; i < threadQty; i++)
            pthread_join(threads[i], NULL);

        for (int i = 0; i < threadQty; i++)
            floatResult += floatSum[i];

        end = chrono::steady_clock::now();

        execTime = chrono::duration_cast<chrono::duration<double>>(end - start);
        executionTime = execTime.count();

        cout << "The float exec time was " << executionTime << " and the end result is " << floatResult << endl << endl;
    } else if (execType == 1) {

        start = chrono::steady_clock::now();

        for (int i = 0; i < threadQty; i++)
            pthread_create(&threads[i], NULL, sumIntArray, (void*)NULL);

        for (int i = 0; i < threadQty; i++)
            pthread_join(threads[i], NULL);

        for (int i = 0; i < threadQty; i++)
            integerResult += intSum[i];

        end = chrono::steady_clock::now();

        execTime = chrono::duration_cast<chrono::duration<double>>(end - start);
        executionTime = execTime.count();

        cout << "The integer exec time was " << executionTime << " and the end result is " << integerResult << endl << endl;
    } 
    
    return 0;
}