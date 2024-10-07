//
// Created by velocitatem on 10/2/24.
//

#include "board.h"

#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

Board::Board(int width, int height, BoardType type, int population) :
    width(width), height(height), type(type), population(population), current_population(0) {
    if (type == GRID) {
        grid = vector<vector<DiscreteAutomaton*>>(height, vector<DiscreteAutomaton*>(width, nullptr));
    }
    else if (type == CONTINUOUS) {
        continuous = vector<ContinuousAutomaton*>(population, nullptr);
    }
}

Board::~Board() {
    if (type == GRID) {
        for (auto& row : grid) {
            for (auto& cell : row) {
                delete cell;
            }
        }
    } else if (type == CONTINUOUS) {
        for (auto& cell : continuous) {
            delete cell;
        }
    }
}

void Board::add_cell(CellularAutomaton *cell) {
    if (type == CONTINUOUS) {
        auto *continuous_cell = dynamic_cast<ContinuousAutomaton*>(cell);
        if (continuous_cell && current_population < population) {
            continuous[current_population] = continuous_cell;
            current_population++;
        }
    }
    else if (type == GRID) {
        auto *discrete_cell = dynamic_cast<DiscreteAutomaton*>(cell);
        if (discrete_cell && discrete_cell->get_x() < width && discrete_cell->get_y() < height) {
            grid[discrete_cell->get_x()][discrete_cell->get_y()] = discrete_cell;
            current_population++;
        }
    }
}


vector<vector<DiscreteAutomaton*>> Board::get_grid() {
    return grid;
}

void Board::set_board(vector<vector<DiscreteAutomaton*>> grid) {
    this->grid = grid;
}

vector<ContinuousAutomaton*> Board::get_continuous() {
    return continuous;
}


int Board::get_current_population() {
    return current_population;
}

CellularAutomaton* Board::get_cell(int x, int y) {
    if (type == GRID && x >= 0 && x < height && y >= 0 && y < width) {
        return grid[x][y];
    }
    else if (type == CONTINUOUS && x >= 0 && x < current_population) {
        return continuous[x];
    }
    return nullptr;
}

void Board::render() {
    if (type == CONTINUOUS) {
        for (int i = 0; i < current_population; i++) {
            // Rendering code for continuous automaton
            // Example: continuous[i]->render();
        }
    }
    else if (type == GRID) {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                CellularAutomaton* c = get_cell(i, j);
                if (!c) {
                    printf("0 ");
                    continue;
                }
                DiscreteAutomaton* cell;
                try {
                    cell = dynamic_cast<DiscreteAutomaton*>(c);
                }
                catch (const std::bad_cast& e) {
                    cell = nullptr;
                }
                if (cell) {
                    printf("%d ", static_cast<int>(cell->get_value()));
                } else {
                    printf("0 ");
                }
            }
            printf("\n");
        }
    }
}
