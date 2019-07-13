#include "node.hpp"

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
    dl.createDLXMatrix(sudokuGrid);
    dl.solved = dl.solve();
    dl.displaySolvedGrid();
    return 0;
}