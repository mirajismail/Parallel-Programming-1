//
// gameoflife.cpp
//
// This code computes the evolution Conway's Game of Life,
//
// This system consists of a two-dimensional grid of cells that are
// either "alive" or "dead".  Time in this system progresses in
// discrete steps.
//
// The state of each cell at the next time step depends on its present
// state and that of its neighbors, in the following way:
//
//   - First, count how many of its 8 closest neighbours are alive.
//   - An alive cell stays alive if that count is 2 or 3, else it dies
//   - A dead cell becomes alive if that count is exactly 3, else it stays dead.
//
// Since the cells at the boundary of the grid would not have enough neighbours to apply
// this rule, we use cells on the other side as neighbours, i.e., 'periodic boundaries'.
//
// The initial state of this system is constructed with a given fraction F of alive
// cells which are (nearly) equally spaced among dead cells.
//
// The code computes the time evolution of an R x C grid for T steps,
// and for each step prints out a line with a representation of the
// state and fraction of alive cells.
//
// The parameters R, C, T, and F should be given as command line arguments.
//
// The representation of the state can be done in one of two ways. The
// first, which is used by default, prints a I or - character for each
// cell. The second, which is selected by giving a fifth command line
// argument of "1", only prints the linear index of the alive cells,
// which is faster in most cases, and should be used for timing.
//
// This code is part of assignment 10 of the 2024 Winter PHY1610 course.
//
// Ramses van Zon, 2024, University of Toronto
// 

#include "celltype.h"
#include "fillcells.h"
#include "outputcells.h"
#include "updatecells.h"
#include <iostream>

int main(int argc, char* argv[]) {
    // Set default simulation parameters then accept command line arguments
    int R = 6;
    int C = 70;
    int T = 20;
    double F = 0.158;
    bool optimized_output = false;
    try {
        if (argc > 1) R = std::stoi(argv[1]);
        if (argc > 2) C = std::stoi(argv[2]);
        if (argc > 3) T = std::stoi(argv[3]);
        if (argc > 4) F = std::stod(argv[4]);
        if (argc > 5) optimized_output = std::stoi(argv[5]);
    } catch(...) {
        std::cout <<
            "\nComputes Conway's game of life\n\n"
            "Usage\n\n"
            "  gameof1d [-h|--help] | [R [C [T [F [OUTPUT]]]]]\n\n"
            ""
            "where\n\n"
            "  R  is the number of rows\n"
            "  C  is the number of columns\n"
            "  T  is the number of time steps to take\n"
            "  F  is the initial fraction of alive cells\n"
            " OUTPUT selects optimized output when sets to 1\n\n";
        if (std::string(argv[1]) != "-h" and std::string(argv[1]) !="--help") {
            std::cerr << "Error in arguments!\n";
            return 1;
        } else
            return 0;
    }
    // Simulation creation
    Cells cell = initial_cells(R, C, F);
    if (optimized_output)
        output_alive_cells(std::cout, 0, cell);
    else
        output_cells(std::cout, 0, cell);
    // Evolution loop
    for (int t = 0; t < T; t++) {
        // One step
        cell = update_all_cells(cell);
        // Output time step, state of cells, and fraction of alive cells
        if (optimized_output)
            output_alive_cells(std::cout, t + 1, cell);
        else
            output_cells(std::cout, t + 1, cell);
    }
} // end main
