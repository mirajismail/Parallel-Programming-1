#include <iostream>
#include <complex>
#include <rarray>

int how_many_iter(std::complex<double> a, int maxiter) {
    std::complex<double> b = a;
    for (int i = 0; i < maxiter; i++) {
        if (std::norm(b) > 4)
            return i;
        b = b * b + a;
    }
    return maxiter;
}

rarray<int, 2> make_mandel_map(double xmin, double xmax,
                                double ymin, double ymax,
                                int npix, int maxiter) {
    rarray<int, 2> mymap(npix, npix);

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < npix; i++) {
        for (int j = 0; j < npix; j++) {
            double x = ((double)i / (double)npix) * (xmax - xmin) + xmin;
            double y = ((double)j / (double)npix) * (ymax - ymin) + ymin;
            std::complex<double> a(x, y);
            mymap[i][j] = how_many_iter(a, maxiter);
        }
    }

    return mymap;
}

int main() {
    double xmin = -2.0, xmax = 1.0;
    double ymin = -1.5, ymax = 1.5;
    int npix = 2000;
    int maxiter = 1000;

    auto mandel = make_mandel_map(xmin, xmax, ymin, ymax, npix, maxiter);

    std::cout << "Mandelbrot computation complete.\n";
    return 0;
}

