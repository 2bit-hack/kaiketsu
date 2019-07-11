#include "node.hpp"

int main() {
    // for now, change this to partially solved sudoku grid
    std::vector<std::vector<uint8_t>> sudokuGrid = {{0, 0, 0, 0, 2, 0, 0, 0, 0},
                                                    {0, 0, 4, 0, 6, 8, 1, 2, 0},
                                                    {0, 0, 7, 1, 0, 0, 0, 0, 8},
                                                    {8, 9, 0, 0, 0, 0, 0, 0, 0},
                                                    {0, 6, 2, 0, 0, 0, 4, 1, 0},
                                                    {0, 0, 0, 0, 0, 0, 0, 9, 3},
                                                    {4, 0, 0, 0, 0, 5, 6, 0, 0},
                                                    {0, 2, 5, 3, 9, 0, 7, 0, 0},
                                                    {0, 0, 0, 0, 8, 0, 0, 0, 0}};
    DancingLinks dl;
    dl.createDLXMatrix(sudokuGrid);
    dl.solve();
    dl.displaySolvedGrid();
    return 0;
}