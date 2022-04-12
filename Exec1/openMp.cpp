#include <iostream>
#include <omp.h>
#include <unistd.h>
#include <chrono>

using namespace std;

const int size = 600;


void directMatricialMultiplication (int resultMatrice[][size], int matricex[][size], int matriceY[][size],  double * execTime) {
    chrono::steady_clock::time_point start = chrono::steady_clock::now();

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            resultMatrice[i][j] = matricex[i][j] * matriceY[i][j];

    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    chrono::duration<double> executionTime = chrono::duration_cast<chrono::duration<double>>(end - start);
    *execTime = executionTime.count();
};

void matricialMultiplication (int resultMatrice[][size], int matricex[][size], int matriceY[][size], double * execTime) {
    chrono::steady_clock::time_point start = chrono::steady_clock::now();

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            resultMatrice[i][j] = matricex[i][j] * matriceY[j][i];

    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    chrono::duration<double> executionTime = chrono::duration_cast<chrono::duration<double>>(end - start);
    *execTime = executionTime.count();
};

void fillMatrice (int matrice[][size], bool revert) {
    if (revert == true) {
        int aux = size * size;
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                matrice[i][j] = aux;
                aux--;
    }
    else {
        int aux = 1;
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                matrice[i][j] = aux;
                aux++;
    }
};

int main ()
{
    double execTimeX, execTimeY;
    int matricex[size][size];
    fillMatrice(matricex, false);
    int matriceY[size][size];
    fillMatrice(matriceY, true);

    int resultMatriceX[size][size];
    matricialMultiplication(resultMatriceX, matricex, matriceY, &execTimeX);
    cout << "Matricial exec time " << execTimeX << endl;
    int resultMatriceY[size][size];
    directMatricialMultiplication(resultMatriceY, matricex, matriceY, &execTimeY);
    cout << "Direct exec time " << execTimeY << endl;

    return 0;
}