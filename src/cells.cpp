//
// Created by velocitatem on 9/27/24.
//
#include "cells.h"

#include <fstream>
#include <map>

using json = nlohmann::json;

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

void DiscreteAutomaton::set_x(int x) { this->x = x; }
void DiscreteAutomaton::set_y(int y) { this->y = y; }
void DiscreteAutomaton::set_value(double value) { this->value = value; }




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
        for (int j = 0; j < board->get_current_population(); j += 1) {
            DiscreteAutomaton *cell = dynamic_cast<DiscreteAutomaton*>(board->get_cell(i, j));
            if (cell) {
                vector<vector<int>> neighbors = {
                    {i-1, j-1}, {i-1, j}, {i-1, j+1},
                    {i, j-1}, {i, j+1},
                    {i+1, j-1}, {i+1, j}, {i+1, j+1}
                };
                int count = 0;
                for (int k = 0; k < neighbors.size(); k += 1) {
                    int x = neighbors[k][0];
                    int y = neighbors[k][1];
                    if (x >= 0 && x < board->get_current_population() && y >= 0 && y < board->get_current_population()) {
                        DiscreteAutomaton *neighbor = dynamic_cast<DiscreteAutomaton*>(board->get_cell(x, y));
                        if (neighbor && neighbor->get_value() > cell->get_value()) {
                            count += 1;
                        }
                    }
                }
                if (cell->get_value()  < 5) {
                    if (count < 2 || count > 3) {
                        cell->set_value(cell->get_value()+count);
                    }
                } else {
                    if (count == 3) {
                        cell->set_value(cell->get_value()-count);
                    }
                }
            }
        }
    }
    board->set_grid(grid);
}
