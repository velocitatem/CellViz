//
// Created by velocitatem on 9/27/24.
//
#include "cells.h"

#include <fstream>
#include <map>

using json = nlohmann::json;

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

void DiscreteAutomaton::set_x(int x) { x = x; }
void DiscreteAutomaton::set_y(int y) { y = y; }
void DiscreteAutomaton::set_value(double value) { value = value; }


SmithLife::SmithLife(int x, int y, double value) : x(x), y(y), value(value) {}
int SmithLife::get_x() { return x; }
int SmithLife::get_y() { return y; }
double SmithLife::get_value() { return value; }

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
    for (int i = 0; i < board.get_height(); i++) {
        for (int j = 0; j < board.get_width(); j++) {
            DiscreteAutomaton *cell = dynamic_cast<DiscreteAutomaton*>(board.get_cell(i, j));
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
                };
                int count = 0;
                for (int k = 0; k < 8; k++) {
                    int x = neighbors[k][0];
                    int y = neighbors[k][1];
                    if (x >= 0 && x < board.get_width() && y >= 0 && y < board.get_height()) {
                        DiscreteAutomaton *neighbor = dynamic_cast<DiscreteAutomaton*>(board.get_cell(x, y));
                        if (neighbor && neighbor->get_value() > cell->get_value()) {
                            count++;
                        }
                    }
                }
                if (cell->get_value() == 1) {
                    if (count < 0 || count > 4) {
                        grid[i][j] = nullptr;
                    }
                } else {
                    if (count == 3) {
                        grid[i][j] = new SmithLife(i, j, 1);
                    }
                }
            }
        }
    }
    board.set_grid(grid);
}


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