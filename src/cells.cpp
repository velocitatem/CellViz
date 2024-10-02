//
// Created by velocitatem on 9/27/24.
//
#include "cells.h"

#include <map>


ParticleLife::ParticleLife(int x, int y, string species) :
x(x), y(y), species(species) {

}

Board ParticleLife::compute(Board *board) {
    map<string, CellularAutomaton> cellular_automaton;
    return *board;
}


