#ifndef DEFINES_H
#define DEFINES_H

// change these to change dimensions of puzzle
#define SIZE 9
#define SIZE_RT 3

// do not change these
#define MAX_ROWS SIZE*SIZE*SIZE
#define MAX_COLS 4*SIZE*SIZE
#define BOXES_ROW SIZE_RT
#define BOXES_COL SIZE_RT

// 0-80: cell constraint
// 81-161: row constraint
// 162-242: col constraint
// 243-323: box constraint
#define CELL_OFFSET 0
#define ROW_OFFSET SIZE*SIZE
#define COL_OFFSET 2*SIZE*SIZE
#define BOX_OFFSET 3*SIZE*SIZE

#endif