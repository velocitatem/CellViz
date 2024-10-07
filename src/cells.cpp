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
    ContinuousAutomaton *all = board->get_continuous();
    for (int i = 0; i < board->get_current_population(); i += 1) {
        CellularAutomaton cell = all[i];
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

Board SmithLife::compute(Board *board) {

    return *board;

}

