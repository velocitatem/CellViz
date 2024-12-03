#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
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
    Board();
    Board(int width, int height, BoardType type, int population = 0);
    // copy constructor
    Board(const Board &board);
    ~Board();

    void add_cell(std::unique_ptr<CellularAutomaton> cell);
    void set_grid(vector<vector<std::unique_ptr<DiscreteAutomaton>>> & grid);
    void set_continuum(vector<std::unique_ptr<ContinuousAutomaton>> & continuous);
    CellularAutomaton* get_cell(int x, int y) const;
    vector<std::unique_ptr<ContinuousAutomaton>> get_continuous();
    vector<vector<std::unique_ptr<DiscreteAutomaton>>> get_grid();
    int get_current_population();
    int get_width();
    int get_height();
    void render();
    // copy assignment
    Board& operator=(const Board &board); // RULE OF 3

private:
    int width;
    int height;
    BoardType type;
    int population;
    int current_population;

    vector<vector<std::unique_ptr<DiscreteAutomaton>>> grid;
    vector<std::unique_ptr<ContinuousAutomaton>> continuous;
};

#endif // BOARD_H