#include <iostream>
#include <chrono>

using namespace std;

const int size = 600;

void directMatricialMultiplication (int resultMatrice[][size], int matriceX[][size], int matriceY[][size],  double * execTime) {
    chrono::steady_clock::time_point start = chrono::steady_clock::now();

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            resultMatrice[i][j] = matriceX[i][j] * matriceY[i][j];

    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    chrono::duration<double> executionTime = chrono::duration_cast<chrono::duration<double>>(end - start);
    *execTime = executionTime.count();
};

void matricialMultiplication (int resultMatrice[][size], int matriceX[][size], int matriceY[][size], double * execTime) {
    chrono::steady_clock::time_point start = chrono::steady_clock::now();

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            resultMatrice[i][j] = matriceX[i][j] * matriceY[j][i];

    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    chrono::duration<double> executionTime = chrono::duration_cast<chrono::duration<double>>(end - start);
    *execTime = executionTime.count();
};

void fillMatrice (int matrice[][size], bool invert = false) {
    if (invert == true) {
        int aux = size * size;
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                matrice[i][j] = aux;
                aux--;
    } else {
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
    int matriceX[size][size];
    fillMatrice(matriceX);
    int matriceY[size][size];
    fillMatrice(matriceY, true);

    int resultMatriceUm[size][size];
    matricialMultiplication(resultMatriceUm, matriceX, matriceY, &execTimeX);
    cout << "Matricial exec time " << execTimeX << endl;

    int resultMatriceDois[size][size];
    directMatricialMultiplication(resultMatriceDois, matriceX, matriceY, &execTimeY);
    cout << "Direct exec time" << execTimeY << endl;

    return 0;
}