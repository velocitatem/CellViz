//
// Created by velocitatem on 10/2/24.
//

#include "board.h"

#include <cstdlib>

Board::Board(int width, int height, BoardType type, int population = 0) {
    if (type == GRID) {
    }
    else if (type == CONTINUOUS) {
        continuous = new CellularAutomaton[population];

    }
}

Board::~Board() {
    delete[] continuous;
}

