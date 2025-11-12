#include <stdio.h>
#include <omp.h>
#include <rarray>

void daxpy_serial(int n, double a, rarray<double,1>& x, rarray<double,1>& y) {
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

    double start = omp_get_wtime();
    daxpy_serial(n, a, x, y);
    double end = omp_get_wtime();

    printf("Serial | Time: %f seconds\n", end - start);
    return 0;
}

