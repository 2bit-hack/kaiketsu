[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

# kaiketsu

Kaiketsu is a (relatively) fast sudoku solver written in C++

![kaiketsu](https://github.com/2bit-hack/kaiketsu/blob/master/img/kaiket2.png "kaiketsu")

It implements Donald Knuth's [Algorithm X](https://en.wikipedia.org/wiki/Knuth%27s_Algorithm_X "algo x")
and [Dancing Links](https://en.wikipedia.org/wiki/Dancing_Links "dancing links").

The original paper can be found [here](https://arxiv.org/abs/cs/0011047 "dlx paper").

This project uses [rang](https://github.com/agauniyal/rang "rang") to provide colors in terminal.
Huge props to the author!

Some puzzles can be found [here](https://sudoku.com/ "puzzles").

## Usage

In `main.cpp`, modify partial sudoku puzzle and save

Run
```
make
./kaiketsu
```

`defines.hpp` contains parameters that can be changed to modify the dimensions of the puzzle.

Run
```
make clean
```
to clean up object and exec files
