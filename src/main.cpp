#include "node.hpp"
#include <chrono>

int main() {
    // for now, change this to partially solved sudoku grid
    std::vector<std::vector<uint8_t>> sudokuGrid = {{9, 6, 0, 0, 0, 11, 0, 0, 15, 3, 0, 2, 0, 0, 1, 13},
                                                    {13, 0, 16, 2, 15, 0, 0, 0, 0, 0, 0, 1, 4, 0, 0, 0},
                                                    {0, 0, 0, 0, 16, 0, 0, 0, 4, 0, 12, 0, 10, 9, 6, 0},
                                                    {15, 4, 0, 0, 14, 0, 0, 0, 0, 0, 0, 0, 0, 12, 0, 0},
                                                    {1, 0, 0, 0, 2, 0, 0, 10, 0, 7, 3, 0, 0, 15, 0, 0},
                                                    {14, 0, 0, 0, 0, 0, 0, 0, 6, 5, 10, 12, 3, 0, 0, 8},
                                                    {0, 0, 2, 5, 0, 6, 0, 0, 8, 15, 0, 16, 0, 1, 0, 9},
                                                    {8, 0, 7, 0, 0, 13, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                    {0, 13, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
                                                    {0, 0, 0, 0, 0, 12, 2, 0, 14, 0, 0, 0, 0, 16, 3, 0},
                                                    {4, 15, 11, 0, 0, 0, 0, 1, 0, 0, 0, 10, 9, 0, 13, 0},
                                                    {5, 0, 10, 12, 0, 0, 0, 0, 0, 0, 0, 0, 8, 11, 0, 1},
                                                    {0, 10, 6, 0, 11, 3, 0, 0, 0, 2, 0, 7, 0, 13, 0, 0},
                                                    {0, 7, 0, 1, 0, 2, 0, 0, 13, 14, 0, 0, 0, 10, 15, 0},
                                                    {0, 0, 0, 0, 13, 0, 8, 0, 0, 16, 4, 0, 0, 0, 0, 3},
                                                    {0, 2, 5, 0, 0, 10, 7, 0, 3, 0, 0, 8, 0, 0, 0, 0},
                                                    };   
    DancingLinks dl;
    auto start = std::chrono::high_resolution_clock::now();
    dl.createDLXMatrix(sudokuGrid);
    dl.solved = dl.solve();
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> total = finish - start;
    dl.displaySolvedGrid(sudokuGrid);
    if(dl.solved)
        std::cout << "\nTime taken: " << rang::fgB::green << total.count() << rang::fgB::gray << "s\n";
    return 0;
}
