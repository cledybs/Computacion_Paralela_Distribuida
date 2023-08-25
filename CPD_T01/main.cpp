#include <iostream>
#include <chrono>

const int MAX = 10;

int main() {
    double A[MAX][MAX], x[MAX], y[MAX];
    int i, j;

    for (i = 0; i < MAX; i++) {
        x[i] = i + 1;
        y[i] = 0;

        for (j = 0; j < MAX; j++) {
            A[i][j] = i * j;
        }
    }

    auto start1 = std::chrono::high_resolution_clock::now();
    for (i = 0; i < MAX; i++) {
        for (j = 0; j < MAX; j++) {
            y[i] += A[i][j] * x[j];
        }
    }

    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed1 = end1 - start1;

    std::cout << "Resultados para el primer bucle:" << std::endl;
    for (i = 0; i < MAX; i++) {
        std::cout << "y[" << i << "] = " << y[i] << std::endl;
    }
    std::cout << "Tiempo para el primer par de bucles: " << elapsed1.count() << " segundos" << std::endl;

    for (i = 0; i < MAX; i++) {
        y[i] = 0;
    }

    auto start2 = std::chrono::high_resolution_clock::now();
    for (j = 0; j < MAX; j++) {
        for (i = 0; i < MAX; i++) {
            y[i] += A[i][j] * x[j];
        }
    }

    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed2 = end2 - start2;

    std::cout << "\nResultados para el segundo par de bucles:" << std::endl;
    for (i = 0; i < MAX; i++) {
        std::cout << "y[" << i << "] = " << y[i] << std::endl;
    }

    std::cout << "Tiempo para el segundo bucle: " << elapsed2.count() << " segundos" << std::endl;

    return 0;
}