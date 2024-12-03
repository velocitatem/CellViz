#include "cells.h"
#include <fstream>
#include <map>
#include <memory>

using json = nlohmann::json;

ParticleLife::ParticleLife() : x(0), y(0), species("") { }
ParticleLife::ParticleLife(int x, int y, string species) : x(x), y(y), species(species) { }
Board ParticleLife::compute(Board *board) {
    map<string, ContinuousAutomaton> cellular_automaton;
    vector<std::unique_ptr<ContinuousAutomaton>>& all = board->get_continuous();
    for (int i = 0; i < board->get_current_population(); i += 1) {
        ContinuousAutomaton& cell = *all[i];
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
void DiscreteAutomaton::set_x(int x) { this->x = x; }
void DiscreteAutomaton::set_y(int y) { this->y = y; }
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
    vector<vector<std::unique_ptr<DiscreteAutomaton>>>& grid = board->get_grid();
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
    std::vector<std::vector<std::unique_ptr<DiscreteAutomaton>>>& grid = board.get_grid();
    for (int i = 0; i < board.get_height(); i++) {
        for (int j = 0; j < board.get_width(); j++) {
            DiscreteAutomaton *cell = dynamic_cast<DiscreteAutomaton*>(board.get_cell(i, j));
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
                for (int k = 0; k < 8; k++) {
                    int x = neighbors[k][0];
                    int y = neighbors[k][1];
                    if (x >= 0 && x < board.get_width() && y >= 0 && y < board.get_height()) {
                        DiscreteAutomaton *neighbor = dynamic_cast<DiscreteAutomaton*>(board.get_cell(x, y));
                        if (neighbor && neighbor->get_value() > 0) {
                            count++;
                        }
                    }
                }
                if (cell->get_value() == 1) {
                    if (count < 2 || count > 3) {
                        cell->set_value(0);
                    }
                } else {
                    if (count == 3) {
                        cell->set_value(1);
                    }
                }
                if (rand() % 100 < 5) {
                    cell->set_value(0);
                }
            }
        }
    }
    board.set_grid(grid);
}

// ======== BASIC LIFE ======== //

BasicLife::BasicLife(int x, int y, double value) : x(x), y(y), value(value) {}
int BasicLife::get_x() { return x; }
int BasicLife::get_y() { return y; }
double BasicLife::get_value() { return value; }
void BasicLife::compute(Board *board) {
    std::vector<std::vector<std::unique_ptr<DiscreteAutomaton>>>& grid = board->get_grid();
    for (int i = 0; i < board->get_height(); i++) {
        for (int j = 0; j < board->get_width(); j++) {
            BasicLife *cell = dynamic_cast<BasicLife*>(board->get_cell(i, j));
            if (cell) {
                double new_value = cell->get_value()+1;
                grid[i][j] = std::make_unique<BasicLife>(i, j, new_value);
            }
        }
    }
    board->set_grid(grid);
}