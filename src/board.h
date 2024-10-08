//
// Created by velocitatem on 10/2/24.
//
#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "cells.h"

class DiscreteAutomaton;
class ContinuousAutomaton;
class CellularAutomaton;

using namespace std;

enum BoardType {
    GRID,
    CONTINUOUS
};

class Board {
public:
    Board(int width, int height, BoardType type, int population = 0);
    // copy constructor
    Board(const Board &board);
    ~Board();

    void add_cell(CellularAutomaton *cell);
    void set_grid(vector<vector<DiscreteAutomaton*>> & grid);
    void set_continuum(vector<ContinuousAutomaton*> & continuous);
    CellularAutomaton* get_cell(int x, int y) const;
    vector<ContinuousAutomaton*> get_continuous() const;
    vector<vector<DiscreteAutomaton*>> get_grid() const;
    int get_current_population();
    void render();
    // TODO: Add a move constructor, copy assignment operator, and move assignment operator.


private:
    int width;
    int height;
    BoardType type;
    int population;
    int current_population;

    vector<vector<DiscreteAutomaton*>> grid;
    vector<ContinuousAutomaton*> continuous;
};

#endif // BOARD_H
