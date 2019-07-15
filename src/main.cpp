#include "node.hpp"
#include <chrono>

int main() {
    // for now, change this to partially solved sudoku grid
    std::vector<std::vector<uint8_t>> sudokuGrid = {{0, 0, 0, 0, 0, 0, 0, 0, 1},
                                                    {0, 0, 0, 0, 0, 0, 0, 2, 3},
                                                    {0, 0, 4, 0, 0, 5, 0, 0, 0},
                                                    {0, 0, 0, 1, 0, 0, 0, 0, 0},
                                                    {0, 0, 0, 0, 3, 0, 6, 0, 0},
                                                    {0, 0, 7, 0, 0, 0, 5, 8, 0},
                                                    {0, 0, 0, 0, 6, 7, 0, 0, 0},
                                                    {0, 1, 0, 0, 0, 4, 0, 0, 0},
                                                    {5, 2, 0, 0, 0, 0, 0, 0, 0}};   
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
