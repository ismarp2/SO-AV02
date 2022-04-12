#include <iostream>
#include <chrono>
#include <pthread.h>

using namespace std;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

const int size = 600;
int currentLine = 0;
const int threadQty = 4;

int matriceX[size][size];
int matriceY[size][size];
int resultMatrice[size][size];

void * directMatricialMultiplication (void * arg) {
    int i;
    
    do{
        pthread_mutex_lock(&lock);
        i = currentLine;
        currentLine++;
        pthread_mutex_unlock(&lock);

        if (i >= size)
            break;

        for (int j = 0; j < size; j++)
            resultMatrice[i][j] = matriceX[i][j] * matriceY[i][j];
    } while(true);

    return nullptr;
};

void * matricialMultiplication (void * arg) {
    int i;
    
    do{
        pthread_mutex_lock(&lock);
        i = currentLine;
        currentLine++;
        pthread_mutex_unlock(&lock);

        if (i >= size)
            break;

        for (int j = 0; j < size; j++)
            resultMatrice[i][j] = matriceX[i][j] * matriceY[j][i];
    } while(true);

    return nullptr;
};

void fillMatrice (int matriz[][size], bool invert) {
    if (invert == true) {
        int aux = size * size;
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                matriz[i][j] = aux;
                aux--;
    } else {
        int aux = 1;
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                matriz[i][j] = aux;
                aux++;
    }
};

int main ()
{
    fillMatrice(matriceX, false);
    fillMatrice(matriceY, true);

    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    pthread_t threads[threadQty];

    for (int i = 0; i < threadQty; i++) {
        int* p;
        pthread_create(&threads[i], NULL, matricialMultiplication, (void*)(p));
    }

    for (int i = 0; i < threadQty; i++)
        pthread_join(threads[i], NULL);
    
    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    chrono::duration<double> execTime = chrono::duration_cast<chrono::duration<double>>(end - start);

    cout << "Exec time " << execTime.count() << endl << endl;

    return 0;
}