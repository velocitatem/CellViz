//
// Created by velocitatem on 10/2/24.
//

#ifndef BOARD_H
#define BOARD_H

#include "cells.h"

class CellularAutomaton;

enum BoardType {
    GRID = 0,
    CONTINUOUS = 1
};

class Board {
public:
    Board(int width, int height, BoardType type, int population);
    ~Board();
    auto get_field();
    void render();
    void add_cell(CellularAutomaton cell);
private:
    int width, height, population, current_population;
    BoardType type;
    CellularAutomaton **grid;
    CellularAutomaton *continuous; //TODO: Change to vector
};


#endif //BOARD_H
