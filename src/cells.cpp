//
// Created by velocitatem on 9/27/24.
//
#include "cells.h"

#include <map>


ParticleLife::ParticleLife(int x, int y, string species) :
x(x), y(y), species(species) {

}

Board ParticleLife::compute(Board *board) {
    map<string, ContinuousAutomaton> cellular_automaton;
    vector<ContinuousAutomaton*> all = board->get_continuous();
    for (int i = 0; i < board->get_current_population(); i += 1) {
        ContinuousAutomaton cell = *all[i];
        //cellular_automaton.insert(make_pair(cell.species, CellularAutomaton()));
    }

    return *board;
}



SmithLife::SmithLife(int x, int y, double value) :
x(x), y(y), value(value)
{
}



int SmithLife::get_x() { return x; }
int SmithLife::get_y() { return y; }

double SmithLife::get_value() { return value; }

void SmithLife::compute(Board *board) {
    vector<vector<DiscreteAutomaton*>> grid = board->get_grid();
    for (int i = 0; i < board->get_current_population(); i += 1) {
        DiscreteAutomaton *cell = grid[i][i];
        if (cell) {
            grid[i][i] = new SmithLife(cell->get_x(), cell->get_y(), cell->get_value()+1);
        }
    }
    board->set_grid(grid);
}

