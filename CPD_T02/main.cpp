#include <iostream>
#include <chrono>

#define R1 512 // filas en mat1
#define C1 512 // columnas en mat1 == R2
#define C2 512 // columnas en mat2
#define blockSize 256

void classicMatMult(int m1[][C1], int m2[][C2], int ans[][C2]) {
    for (int i = 0; i < R1; i++) {
        for (int j = 0; j < C2; j++) {
            ans[i][j] = 0;

            for (int k = 0; k < C1; k++) {
                ans[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
}

void blockedMultMat(int m1[][C1], int m2[][C2], int ans[][C2]) {
    for (int i = 0; i < R1; i += blockSize) {
        for (int j = 0; j < C2; j += blockSize) {
            for (int k = 0; k < C1; k += blockSize) {
                // mult de bloque m1(i:i+blockSize-1, k:k+blockSize-1)
                // con bloque m2(k:k+blockSize-1, j:j+blockSize-1)
                for (int ii = i; ii < i + blockSize && ii < R1; ++ii) {
                    for (int jj = j; jj < j + blockSize && jj < C2; ++jj) {
                        for (int kk = k; kk < k + blockSize && kk < C1; ++kk) {
                            ans[ii][jj] += m1[ii][kk] * m2[kk][jj];
                        }
                    }
                }
            }
        }
    }
}


int main() {
    int m1[R1][C1];
    int m2[C1][C2];
    int ans[R1][C2] = {0};

    for (int i = 0; i < R1; ++i)
        for (int j = 0; j < C1; ++j)
            m1[i][j] = i + j;

    for (int i = 0; i < C1; ++i)
        for (int j = 0; j < C2; ++j)
            m2[i][j] = i - j;

    auto start1 = std::chrono::high_resolution_clock::now();
    classicMatMult(m1, m2, ans);
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed1 = end1 - start1;
    std::cout << "Tiempo para la multiplicacion clasica: " << elapsed1.count() << " segundos" << std::endl;

    /*std::cout << "Resultado de la multiplicacion clasica:" << std::endl;
    for (int i = 0; i < R1; ++i) {
        for (int j = 0; j < C2; ++j) {
            std::cout << ans[i][j] << "\t";
        }
        std::cout << std::endl;
    }*/

    //std::cout << "---------------------------------------------------------------------------------------";
    for (int i = 0; i < R1; ++i)
        for (int j = 0; j < C2; ++j)
            ans[i][j] = 0;

    auto start2 = std::chrono::high_resolution_clock::now();
    blockedMultMat(m1, m2, ans);
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed2 = end2 - start2;
    std::cout << "Tiempo para la multiplicacion por bloques: " << elapsed2.count() << " segundos" << std::endl;

    /*std::cout << "Resultado de la multiplicacion por bloques:" << std::endl;
    for (int i = 0; i < R1; ++i) {
        for (int j = 0; j < C2; ++j) {
            std::cout << ans[i][j] << "\t";
        }
        std::cout << std::endl;
    }*/

    return 0;
}
