// outputcells.cpp
//
// see outputcells.h for documentation
//
// This code is part of assignment 10 of the 2024 Winter PHY1610 course.
//
// Ramses van Zon, 2024, University of Toronto
// 

#include "outputcells.h"
#include <omp.h>

void output_cells(std::ostream& out, int step, const Cells& cell)
{
    const int num_rows = cell.extent(0);
    const int num_cols = cell.extent(1);
    const char on_char = 'I', off_char = '-';
    double alive_fraction = 0.0;
    for (auto& onecell: cell)
        if (onecell == alive)
            alive_fraction++;
    alive_fraction /= cell.size();
    out << step << "\t";
    for (int j = 0; j < num_cols; j++)
        if (cell[0][j] == alive)
            out << on_char;
        else
            out << off_char;
    out << " " << alive_fraction << "\n";
    for (int i = 1; i < num_rows; i++) {
        out << "\t";
        for (int j = 0; j < num_cols; j++)
            if (cell[i][j] == alive)
                out << on_char;
            else
                out << off_char;
        out << "\n";
    }
}

void output_alive_cells(std::ostream& out, int step, const Cells& cell)
{
    const int num_rows = cell.extent(0);
    const int num_cols = cell.extent(1);

    // count alive cells per row
    std::vector<int> row_counts(num_rows, 0);

    #pragma omp parallel for
    for (int i = 0; i < num_rows; i++) {
        int cnt = 0;
        for (int j = 0; j < num_cols; j++)
            if (cell[i][j] == alive)
                cnt++;
        row_counts[i] = cnt;
    }

    // PREFIX SUM to compute starting offset per row
    std::vector<int> row_start(num_rows, 0);

    for (int i = 1; i < num_rows; i++)
        row_start[i] = row_start[i-1] + row_counts[i-1];

    int alive_count = row_start[num_rows - 1] + row_counts[num_rows - 1];
    rvector<int> alive_list(alive_count);

    // parallel fill alive_list each row writes to its deterministic slice
    #pragma omp parallel for
    for (int i = 0; i < num_rows; i++) {
        int n = row_start[i];
        for (int j = 0; j < num_cols; j++)
            if (cell[i][j] == alive)
                alive_list[n++] = i * num_cols + j;
    }

    double alive_fraction =
        double(alive_count) / double(cell.size());

    out << step << "\t/";
    for (const auto &x : alive_list)
        out << x << '/';
    out << "\t" << alive_fraction << "\n";
}
