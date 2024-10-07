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
    Board(const Board &board) {
        width = board.width;
        height = board.height;
        type = board.type;
        population = board.population;
        current_population = board.current_population;
        grid = board.grid;
        continuous = board.continuous;
    }
    ~Board();

    void add_cell(CellularAutomaton *cell);
    void set_board(vector<vector<DiscreteAutomaton*>> grid);
    void set_continuum(vector<ContinuousAutomaton*> continuous);
    CellularAutomaton* get_cell(int x, int y);
    vector<ContinuousAutomaton*> get_continuous();
    vector<vector<DiscreteAutomaton*>> get_grid();
    int get_current_population();
    void render();

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
