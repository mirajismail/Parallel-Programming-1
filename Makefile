CXX = g++
CXXFLAGS += -O3 -fopenmp -I$(HOME)/.local/include
LDFLAGS  += -L$(HOME)/.local/lib

all: mandelbrot serial_daxpy parallel_daxpy daxpy_large

mandelbrot: Problem\ 2/mandelbrot_set.cpp
	$(CXX) $(CXXFLAGS) "Problem 2/mandelbrot_set.cpp" -o "Problem 2/mandelbrot" $(LDFLAGS)

serial_daxpy: Problem\ 3/serial_daxpy.cpp
	$(CXX) $(CXXFLAGS) "Problem 3/serial_daxpy.cpp" -o "Problem 3/serial_daxpy" $(LDFLAGS)

parallel_daxpy: Problem\ 3/parallel_daxpy.cpp
	$(CXX) $(CXXFLAGS) "Problem 3/parallel_daxpy.cpp" -o "Problem 3/parallel_daxpy" $(LDFLAGS)

daxpy_large: Problem\ 3/daxpy_large.cpp
	$(CXX) $(CXXFLAGS) "Problem 3/daxpy_large.cpp" -o "Problem 3/daxpy_large" $(LDFLAGS)


clean:
	rm -f "Problem 2/mandelbrot" "Problem 3/serial_daxpy" "Problem 3/parallel_daxpy" "Problem 3/daxpy_large"

