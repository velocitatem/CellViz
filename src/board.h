//
// Created by velocitatem on 10/2/24.
//

#ifndef BOARD_H
#define BOARD_H
#include "cells.h"

enum BoardType {
    GRID = 0,
    CONTINUOUS = 1
};

class Board {
public:
    Board(int width, int height, BoardType type, int population);
    ~Board();
private:
    CellularAutomaton **grid;
    CellularAutomaton *continuous;
};


#endif //BOARD_H
