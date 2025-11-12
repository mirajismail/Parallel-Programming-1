#include <iostream>
#include <omp.h>
#include <rarray>

void daxpy_serial(int n, double a, double *x, double *y) {
    for (int i = 0; i < n; i++)
        y[i] = a * x[i] + y[i];
}

void daxpy_parallel(int n, double a, double *x, double *y, int num_threads) {
    omp_set_num_threads(num_threads);
    #pragma omp parallel for
    for (int i = 0; i < n; i++)
        y[i] = a * x[i] + y[i];
}

int main() {
    const int NX = 1000, NY = 1000, NZ = 1000;
    const size_t N = (size_t)NX * NY * NZ; // 1e9
    const double a = 2.0;

    rarray<double,3> x(NX, NY, NZ);
    rarray<double,3> y(NX, NY, NZ);

    // initialize
    for (size_t i = 0; i < NX; i++)
        for (size_t j = 0; j < NY; j++)
            for (size_t k = 0; k < NZ; k++) {
                x[i][j][k] = 1.0;
                y[i][j][k] = 2.0;
            }

    double start, end;

    // ---- Serial ----
    start = omp_get_wtime();
    daxpy_serial(N, a, &x[0][0][0], &y[0][0][0]);
    end = omp_get_wtime();
    std::cout << "Serial time: " << end - start << " s\n";

    // ---- Parallel ----
    for (int threads : {4, 8, 16, 32, 64}) {
        // reset y
        for (size_t i = 0; i < NX; i++)
            for (size_t j = 0; j < NY; j++)
                for (size_t k = 0; k < NZ; k++)
                    y[i][j][k] = 2.0;

        start = omp_get_wtime();
        daxpy_parallel(N, a, &x[0][0][0], &y[0][0][0], threads);
        end = omp_get_wtime();
        std::cout << threads << " threads: " << end - start << " s\n";
    }
}

