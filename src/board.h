//
// Created by velocitatem on 10/2/24.
//

#ifndef BOARD_H
#define BOARD_H

#include "cells.h"

class CellularAutomaton;
class DiscreteAutomaton;
class ContinuousAutomaton;

enum BoardType {
    GRID = 0,
    CONTINUOUS = 1
};

class Board {
public:
    Board(int width, int height, BoardType type, int population);
    ~Board();
    DiscreteAutomaton ** get_grid();
    ContinuousAutomaton * get_continuous();
    void render();
    void add_cell(CellularAutomaton *cell);
    int get_current_population();
    int get_width(); int get_height();

private:
    int width, height, population, current_population;
    BoardType type;
    DiscreteAutomaton **grid;
    ContinuousAutomaton *continuous; //TODO: Change to vector
};


#endif //BOARD_H
