#include <iostream>
#include <vector>
#include <omp.h>
#include <ctime>

int main() {
    const int N = 1000; // Размерность матриц

    // Создание матриц A, B и C
    std::vector<std::vector<double>> A(N, std::vector<double>(N));
    std::vector<std::vector<double>> B(N, std::vector<double>(N));
    std::vector<std::vector<double>> C(N, std::vector<double>(N, 0.0));

    // Инициализация матриц случайными числами
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            A[i][j] = rand() % 100; // Случайные числа от 0 до 99
            B[i][j] = rand() % 100;
        }
    }

    // Замер времени начала
    double start_time = omp_get_wtime();

    // Перемножение матриц с использованием OpenMP
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    // Замер времени окончания
    double end_time = omp_get_wtime();

    // Вывод времени выполнения
    std::cout << "Время выполнения: " << end_time - start_time << " секунд" << std::endl;

    return 0;
}
