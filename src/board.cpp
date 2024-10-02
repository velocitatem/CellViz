//
// Created by velocitatem on 10/2/24.
//

#include "board.h"

#include <cstdlib>
#include <map>

Board::Board(int width, int height, BoardType type, int population = 0) :
width(width), height(height), type(type), population(population), current_population(0) {
    if (type == GRID) {
    }
    else if (type == CONTINUOUS) {
        continuous = new CellularAutomaton[population];

    }
}

Board::~Board() {
}

auto Board::get_field() {
    //return type == CONTINUOUS ? continuous : grid;
}

void Board::add_cell(CellularAutomaton cell) {
    if (type == CONTINUOUS) {
        continuous[current_population] = cell;
    }
    //TODO: Grid
}



void Board::render() {
    if (type == CONTINUOUS) {
        for (int i = 0; i < population; i++) {
            CellularAutomaton automaton = continuous[i];

        }
    }
    else if (type == GRID) {

    }

}
