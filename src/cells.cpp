//
// Created by velocitatem on 9/27/24.
//
#include "cells.h"

#include <fstream>
#include <map>

using json = nlohmann::json;

ParticleLife::ParticleLife() : x(0), y(0), species("") { }
ParticleLife::ParticleLife(int x, int y, string species) : x(x), y(y), species(species) { }
Board ParticleLife::compute(Board *board) {
    map<string, ContinuousAutomaton> cellular_automaton;
    vector<ContinuousAutomaton*> all = board->get_continuous();
    for (int i = 0; i < board->get_current_population(); i += 1) {
        ContinuousAutomaton cell = *all[i];
        //cellular_automaton.insert(make_pair(cell.species, CellularAutomaton()));
    }
    return *board;
}

DiscreteAutomaton::DiscreteAutomaton() : x(0), y(0), value(0) { }
DiscreteAutomaton::DiscreteAutomaton(int x, int y, double value) : x(x), y(y), value(value) { }
DiscreteAutomaton::DiscreteAutomaton(const DiscreteAutomaton &cell) {
    x = cell.x;
    y = cell.y;
    value = cell.value;
}
void DiscreteAutomaton::set_x(int x) { x = x; }
void DiscreteAutomaton::set_y(int y) { y = y; }
void DiscreteAutomaton::set_value(double value) { this->value = value; }
// == op
bool DiscreteAutomaton::operator==(const DiscreteAutomaton &cell) const {
    const double EPSILON = 1e-9;
    return x == cell.x && y == cell.y && std::abs(value - cell.value) < EPSILON;
}

SmithLife::SmithLife(int x, int y, double value) : x(x), y(y), value(value) {}
int SmithLife::get_x() { return x; }
int SmithLife::get_y() { return y; }
double SmithLife::get_value() { return value; }
void SmithLife::set_value(double value) {
    this->value = value;
}


SmithLife::~SmithLife() {}

void CellularAutomaton::compute(Board *board) {
    vector<vector<DiscreteAutomaton*>> grid = board->get_grid();
    for (int i = 0; i < board->get_height(); i += 1) {
        for (int j = 0; j < board->get_width(); j += 1) {
            DiscreteAutomaton *cell = dynamic_cast<DiscreteAutomaton*>(board->get_cell(i, j));
            if (cell) {
                int neighbors[8][2] = {
                    {i-1, j-1},
                    {i-1, j},
                    {i-1, j+1},
                    {i, j-1},
                    {i, j+1},
                    {i+1, j-1},
                    {i+1, j},
                    {i+1, j+1}
                };
                int count = 0;
                for (int k = 0; k < 8; k += 1) {
                    int x = neighbors[k][0];
                    int y = neighbors[k][1];
                    if (x >= 0 && x < board->get_width() && y >= 0 && y < board->get_height()) {
                        DiscreteAutomaton *neighbor = dynamic_cast<DiscreteAutomaton*>(board->get_cell(x, y));
                        if (neighbor && neighbor->get_value() > cell->get_value()) {
                            count += 1;
                        }
                    }
                }
                if (cell->get_value()  < 5) {
                    if (count < 2 || count > 3) {
                        cell->set_value(cell->get_value()+20*count);
                    }
                } else {
                }
                if (cell->get_value() > 80) {
                    // cell dies
                    grid[i][j] = nullptr;
                }
            }
        }
    }
    board->set_grid(grid);
}


void SmithLife::compute(Board &board) {
    std::vector<std::vector<DiscreteAutomaton*>> grid = board.get_grid();
    // easier access more local and less overhead
    for (int i = 0; i < board.get_height(); i++) {
        for (int j = 0; j < board.get_width(); j++) {
            DiscreteAutomaton *cell = dynamic_cast<DiscreteAutomaton*>(board.get_cell(i, j));
            // getting the cell at each point of teh board
            if (cell) {
                // game of life rules
                int neighbors[8][2] = {
                        {i-1, j-1},
                        {i-1, j},
                        {i-1, j+1},
                        {i, j-1},
                        {i, j+1},
                        {i+1, j-1},
                        {i+1, j},
                        {i+1, j+1}
                }; // pre-defined neighbor coordinates
                int count = 0;
                for (int k = 0; k < 8; k++) {
                    int x = neighbors[k][0];
                    int y = neighbors[k][1];
                    if (x >= 0 && x < board.get_width() && y >= 0 && y < board.get_height()) { // verify is within bounds
                        // get the neighbor if it exists
                        DiscreteAutomaton *neighbor = dynamic_cast<DiscreteAutomaton*>(board.get_cell(x, y));
                        if (neighbor && neighbor->get_value() > 0) {
                        // compare and see if values i greater than the current cell
                            count++;
                        }
                    }
                }
                if (cell->get_value() == 1) {
                    if (count < 2 || count > 3) { // we see if we kill the cell
                        auto pointer_to_cell = grid[i][j];
                        auto smith_life = dynamic_cast<SmithLife*>(pointer_to_cell);
                        smith_life->set_value(0);
                    }
                } else {
                    if (count == 3) {
                        auto pointer_to_cell = grid[i][j];
                        auto smith_life = dynamic_cast<SmithLife*>(pointer_to_cell);
                        smith_life->set_value(1);
                    }
                }
            }
        }
    }
    board.set_grid(grid); // actually update teh board
}



// ======== BASIC LIFE ======== //

BasicLife::BasicLife(int x, int y, double value) : x(x), y(y), value(value) {}
int BasicLife::get_x() { return x; }
int BasicLife::get_y() { return y; }
double BasicLife::get_value() { return value; }
void BasicLife::compute(Board *board) {
    std::vector<std::vector<DiscreteAutomaton*>> grid = board->get_grid();
    for (int i = 0; i < board->get_height(); i++) {
        for (int j = 0; j < board->get_width(); j++) {
            BasicLife *cell = dynamic_cast<BasicLife*>(board->get_cell(i, j));
            if (cell) {
                double new_value = cell->get_value()+1;
                cell = new BasicLife(i, j, new_value);
                grid[i][j] = cell;
            }
        }
    }
    board->set_grid(grid);
}