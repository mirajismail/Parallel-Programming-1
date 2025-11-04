CXX = g++
CXXFLAGS += -O3 -fopenmp -I$(HOME)/.local/include
LDFLAGS  += -L$(HOME)/.local/lib

all: mandelbrot

mandelbrot: Problem\ 2/mandelbrot_set.cpp
	$(CXX) $(CXXFLAGS) "Problem 2/mandelbrot_set.cpp" -o "Problem 2/mandelbrot" $(LDFLAGS)

clean:i
	rm -f "Problem 2/mandelbrot"
