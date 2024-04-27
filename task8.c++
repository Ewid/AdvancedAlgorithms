#include <iostream>
#include <pthread.h>
using namespace std;


struct ThreadArgs {
    int row;
    int **A;
    int **B;
    int **C;
    int colsB;
    int colsA;
};


void* multiplyRow(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    int row = args->row;
    for (int j = 0; j < args->colsB; j++) {
        args->C[row][j] = 0;
        for (int k = 0; k < args->colsA; k++) {
            args->C[row][j] += args->A[row][k] * args->B[k][j];
        }
    }
    pthread_exit(NULL);
    return NULL;
}

int main() {
    int rowsA = 3, colsA = 3, rowsB = 3, colsB = 3;

    int** A = new int*[rowsA];
    int** B = new int*[rowsB];
    int** C = new int*[rowsA];
    for (int i = 0; i < rowsA; i++) {
        A[i] = new int[colsA] {1, 2, 3,}; 
    }
    for (int i = 0; i < rowsB; i++) {
        B[i] = new int[colsB] {4, 5, 6}; 
    }
    for (int i = 0; i < rowsA; i++) {
        C[i] = new int[colsB](); 
    }

    pthread_t* threads = new pthread_t[rowsA];
    ThreadArgs* args = new ThreadArgs[rowsA];

    for (int i = 0; i < rowsA; i++) {
        args[i].row = i;
        args[i].A = A;
        args[i].B = B;
        args[i].C = C;
        args[i].colsB = colsB;
        args[i].colsA = colsA;
        pthread_create(&threads[i], NULL, multiplyRow, (void*)&args[i]);
    }

    for (int i = 0; i < rowsA; i++) {
        pthread_join(threads[i], NULL);
    }

    cout << "Matrix C (Result of A * B):" << endl;
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < rowsA; i++) {
        delete[] A[i];
        delete[] C[i];
    }
    for (int i = 0; i < rowsB; i++) {
        delete[] B[i];
    }
    delete[] A;
    delete[] B;
    delete[] C;
    delete[] threads;
    delete[] args;

    return 0;
}
