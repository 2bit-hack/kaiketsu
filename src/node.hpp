// contains definitions for Node, DancingLinks
#ifndef NODE_H
#define NODE_H

#include "defines.hpp"
#include "rang.hpp"
#include <iostream>
#include <vector>
#include <tuple>

// util functions
uint8_t getDigitCount(uint8_t x) {
    uint8_t count = 0;
    while(x != 0) {
        x = x / 10;
        count++;
    }
    return count;
}

void printnSpaces(uint8_t n) {
    while(n--) {
        std::cout << " ";
    }
}

// circularly connected to four directions
// also connected to node that identifies column
struct Node {

    Node* left = this;
    Node* right = this;
    Node* up = this;
    Node* down = this;
    Node* cHead = this;

    // useful for S-heuristic
    int size = 0;
    // row, column, value
    std::tuple<uint8_t, uint8_t, uint8_t> info = {-1, -1, -1};

    Node(uint8_t r, uint8_t c, uint8_t v) {
        std::get<0>(info) = r;
        std::get<1>(info) = c;
        std::get<2>(info) = v;
    }
};

class DancingLinks {

public:
    std::vector<std::vector<Node*>> DLXMatrix;
    // the header to the col headers(main header)
    Node* head = new Node(-1, -1, -1);
    std::vector<std::tuple<int, int, int>> infoSol;
    std::vector<Node*> toCover;
    bool solved;
    // required for cleanup
    std::vector<Node*> coveredCols;

    // returns pointer to smallest column for S-heuristic
    Node* getSmallestCol() {
        int min = __INT_MAX__;
        Node* minNode = nullptr;
        for(Node* cNode = head->right; cNode != head; cNode = cNode->right) {
            if(cNode->size < min) {
                min = cNode->size;
                minNode = cNode;
            }
        }
        return minNode;
    }

    // add column header to main header
    void addColToHead(Node* node) {
        // if head is unconnected
        if(head->right == head) {
            head->right = node;
            node->left = head;
            node->right = head;
        }
        // if head is connected
        else {
            Node* rightMost = head->right;
            while(rightMost->right != head) {
                if(rightMost == node)
                    return;
                rightMost = rightMost->right;
            }
            rightMost->right = node;
            node->left = rightMost;
            node->right = head;
        }
    }

    // cover column node and associated rows
    void cover(Node* node) {
        // cover column node
        node->right->left = node->left;
        node->left->right = node->right;
        // cover every node row below column node
        for(Node* n1 = node->down; n1 != node; n1 = n1->down) {
            for(Node* n2 = n1->right; n2 != n1; n2 = n2->right) {
                    n2->down->up = n2->up;
                    n2->up->down = n2->down;
                    n2->cHead->size--;
            }
        }
    }

    // uncover column node and associated rows
    void uncover(Node* node) {
        // uncover every node row below column node
        for(Node* n1 = node->up; n1 != node; n1 = n1->up) {
            for(Node* n2 = n1->left; n2 != n1; n2 = n2->left) {
                n2->cHead->size++;
                n2->up->down = n2;
                n2->down->up = n2;
            }
        }
        // uncover column node
        node->left->right = node;
        node->right->left = node;
    }

    bool solve() {

        // no more column constraints; complete solution
        if(head->right == head) {
            return true;
        }
        else {
            // choose smallest column; S-heuristic
            Node* currCol = getSmallestCol();
            // column constraint has no solution!

            if(currCol->size == 0) {
                return false;
            }

            // add to existing solution and remove column
            // and associated rows
            cover(currCol);
            coveredCols.push_back(currCol);

            // for every row in current column
            for(Node* rowNode = currCol->down; rowNode != currCol;
            rowNode = rowNode->down) {
                // add to partial solution
                infoSol.push_back(rowNode->info);
                // for every other column that is satisfied by this row
                for(Node* otherColNode = rowNode->right; otherColNode != rowNode;
                otherColNode = otherColNode->right) {
                    // cover those columns
                    cover(otherColNode->cHead);
                    coveredCols.push_back(otherColNode->cHead);
                }
                // recursively solve on reduced structure
                if(solve())
                    return true;

                // nope, doesn't work :(
                // remove from partial solution
                // uncover those columns
                infoSol.pop_back();
                for(Node* otherColNode = rowNode->left; otherColNode != rowNode;
                otherColNode = otherColNode->left) {
                    uncover(otherColNode->cHead);
                    coveredCols.pop_back();
                }
            }
            uncover(currCol);
            coveredCols.pop_back();
            return false;
        }
    }

    // creates DLX matrix from original SIZE x SIZE sudoku grid
    void createDLXMatrix(const std::vector<std::vector<uint8_t>>& sudokuGrid) {
        int matrixRow = 0;
        std::vector<std::vector<Node*>> DLXMatrix(MAX_ROWS, std::vector<Node*>(MAX_COLS, nullptr));
        Node *cellConst, *rowConst, *colConst, *boxConst;
        // constraint 1: (row r, col c) has a value
        // constraint 2: row r has value v
        // constraint 3: col c has value v
        // constraint 4: box b has value v
        for(uint8_t _r = 0; _r < SIZE; _r++) {
            for(uint8_t _c = 0; _c < SIZE; _c++) {
                // if given a value for a cell, generate 1 row
                // (row, col, given val)
                if(sudokuGrid[_r][_c] != 0) {
                    uint8_t g = sudokuGrid[_r][_c] - 1; 
                    cellConst = DLXMatrix[matrixRow][CELL_OFFSET + (_r * SIZE) + _c] = new Node(_r+1, _c+1, g+1);
                    rowConst = DLXMatrix[matrixRow][ROW_OFFSET + (_r * SIZE) + g] = new Node(_r+1, _c+1, g+1);
                    colConst = DLXMatrix[matrixRow][COL_OFFSET + (_c * SIZE) + g] = new Node(_r+1, _c+1, g+1);
                    uint8_t _b = ((_r / BOXES_ROW) * SIZE_RT) + (_c / BOXES_COL);
                    boxConst = DLXMatrix[matrixRow][BOX_OFFSET + (_b * SIZE) + g] = new Node(_r+1, _c+1, g+1);

                    // remember to cover these given values
                    toCover.push_back(cellConst);

                    matrixRow++;

                    cellConst->left = boxConst;
                    cellConst->right = rowConst;
                    rowConst->left = cellConst;
                    rowConst->right = colConst;
                    colConst->left = rowConst;
                    colConst->right = boxConst;
                    boxConst->left = colConst;
                    boxConst->right = cellConst;

                    continue;
                }
                // else generate 9 rows
                // for every val from 1 to SIZE, (row, col, val)
                for(uint8_t _v = 0; _v < SIZE; _v++) {
                    cellConst = DLXMatrix[matrixRow][CELL_OFFSET + (_r * SIZE) + _c] = new Node(_r+1, _c+1, _v+1);
                    rowConst = DLXMatrix[matrixRow][ROW_OFFSET + (_r * SIZE) + _v] = new Node(_r+1, _c+1, _v+1);
                    colConst = DLXMatrix[matrixRow][COL_OFFSET + (_c * SIZE) + _v] = new Node(_r+1, _c+1, _v+1);
                    uint8_t _b = ((_r / BOXES_ROW) * SIZE_RT) + (_c / BOXES_COL);
                    boxConst = DLXMatrix[matrixRow][BOX_OFFSET + (_b * SIZE) + _v] = new Node(_r+1, _c+1, _v+1);

                    cellConst->left = boxConst;
                    cellConst->right = rowConst;
                    rowConst->left = cellConst;
                    rowConst->right = colConst;
                    colConst->left = rowConst;
                    colConst->right = boxConst;
                    boxConst->left = colConst;
                    boxConst->right = cellConst;

                    matrixRow++;
                }
            }
        }

        Node* colHead;
        Node* colRow;
        // for every column in the sparse matrix,
        // create a column header, link all the row nodes,
        // and add column header to main header
        for(int i = 0; i < MAX_COLS; i++) {
            colHead = new Node(-1, -1, -1);
            colRow = colHead;
            for(int j = 0; j < MAX_ROWS; j++) {
                if(DLXMatrix[j][i] != nullptr) {
                    DLXMatrix[j][i]->up = colRow;
                    colRow->down = DLXMatrix[j][i];
                    DLXMatrix[j][i]->down = colHead;
                    colHead->up = DLXMatrix[j][i];
                    DLXMatrix[j][i]->cHead = colHead;
                    colHead->size++;
                    colRow = DLXMatrix[j][i];
                }
            }
            addColToHead(colHead);
        }

        // cover all the given values
        for(Node* rowNode: toCover) {
            cover(rowNode->cHead);
            coveredCols.push_back(rowNode->cHead);
            infoSol.push_back(rowNode->info);
            for(Node* otherColNode = rowNode->right; otherColNode != rowNode;
                otherColNode = otherColNode->right) {
                    cover(otherColNode->cHead);
                    coveredCols.push_back(otherColNode->cHead);
            }
        }

        this->DLXMatrix = DLXMatrix;
    }

    // displays solution in SIZE x SIZE matrix
    void displaySolvedGrid(const std::vector<std::vector<uint8_t>>& sudokuGrid) {
        std::cout << "\n";
        if(solved) {
            int solvedGrid[SIZE][SIZE];
            for(auto sol: infoSol) {
                solvedGrid[std::get<0>(sol) - 1][std::get<1>(sol) - 1] = std::get<2>(sol);
            }
            for(uint8_t r = 0; r < SIZE; r++) {
                if(r % SIZE_RT == 0 && r != 0) {
                    for(uint8_t i = 0; i < (2 * SIZE) + SIZE_RT
                    + ((getDigitCount(SIZE)-1)*SIZE) + getDigitCount(SIZE)-1; i++) {
                        std::cout << rang::fgB::green << "-";
                    }
                    std::cout << "\n";
                }
                for(uint8_t c = 0; c < SIZE; c++) {
                    if(c % SIZE_RT == 0 && c != 0) {
                        std::cout << rang::fgB::green <<  "| ";
                    }
                    if(sudokuGrid[r][c] == 0)
                        std::cout << rang::fgB::gray << solvedGrid[r][c] << " ";
                    else
                        std::cout << rang::fgB::cyan << solvedGrid[r][c] << " ";
                    printnSpaces(getDigitCount(SIZE) - getDigitCount(solvedGrid[r][c]));
                }
                std::cout << "\n";
            }
        }
        else
            std::cout << rang::fgB::red << "No solutions found!\n\n";
    }

    // cleanup time
    ~DancingLinks() {
        for(auto nodeRow: DLXMatrix) {
            for(auto node: nodeRow) {
                delete node;
            }
        }

        if(solved) {
            for(auto colNode: coveredCols) {
                delete colNode;
            }
        }

        delete head;
    }

    // debug functions go here

    int debug_numCols() {
        int counter = 0;
        for(Node* n = head->right; n != head; n = n->right) {
            counter++;
        }
        return counter;
    }

    void debug_numSols() {
        std::cout << infoSol.size() << "\n";
    }

    void debug_printSol() {
        for(auto sol: infoSol) {
            std::cout << std::get<0>(sol) << " " << std::get<1>(sol) << " " <<
            std::get<2>(sol) << "\n";
        }
    }
};

#endif