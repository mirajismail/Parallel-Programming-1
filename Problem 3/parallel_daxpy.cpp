#include <stdio.h>
#include <omp.h>
#include <rarray>

void daxpy_parallel(int n, double a, rarray<double,1>& x, rarray<double,1>& y, int num_threads) {
    omp_set_num_threads(num_threads);
    #pragma omp parallel for
    for (int i = 0; i < n; i++)
        y[i] = a * x[i] + y[i];
}

int main() {
    int n = 10000000;
    double a = 2.0;

    rarray<double,1> x(n);
    rarray<double,1> y(n);

    for (int i = 0; i < n; i++) {
        x[i] = 1.0;
        y[i] = 2.0;
    }

    int thread_counts[] = {4, 8, 16, 32, 64};
    int num_configs = sizeof(thread_counts) / sizeof(thread_counts[0]);

    for (int t = 0; t < num_configs; t++) {
        int threads = thread_counts[t];
        double start = omp_get_wtime();

        daxpy_parallel(n, a, x, y, threads);

        double end = omp_get_wtime();
        printf("Threads: %2d | Time: %f seconds\n", threads, end - start);
    }

    return 0;
}

