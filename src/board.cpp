#include "board.h"

#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

Board::Board() : width(0), height(0), type(GRID), population(0), current_population(0) {}
Board::Board(int width, int height, BoardType type, int population) :
    width(width), height(height), type(type), population(population), current_population(0) {
    if (type == GRID) {
        grid = vector<vector<std::unique_ptr<DiscreteAutomaton>>>(height, vector<std::unique_ptr<DiscreteAutomaton>>(width, nullptr));
    }
    else if (type == CONTINUOUS) {
        continuous = vector<std::unique_ptr<ContinuousAutomaton>>(population, nullptr);
    }
}

Board::Board(const Board &board) {
    width = board.width;
    height = board.height;
    type = board.type;
    population = board.population;
    current_population = board.current_population;
    if (type == GRID) {
        grid = board.grid;
    }
    else if (type == CONTINUOUS) {
        continuous = board.continuous;
    }
}

Board& Board::operator=(const Board &board) {
    if (this == &board) {
        return *this;
    }
    width = board.width;
    height = board.height;
    type = board.type;
    population = board.population;
    current_population = board.current_population;
    if (type == GRID) {
        grid = board.grid;
    }
    else if (type == CONTINUOUS) {
        continuous = board.continuous;
    }
    cout << "Board assignment operator called" << endl;
    return *this;
}

Board::~Board() {
    // No need to manually delete cells, smart pointers will handle it
}

void Board::add_cell(std::unique_ptr<CellularAutomaton> cell) {
    if (type == CONTINUOUS) {
        auto *continuous_cell = dynamic_cast<ContinuousAutomaton*>(cell.get());
        if (continuous_cell && current_population < population) {
            continuous[current_population] = std::move(cell);
            current_population++;
        }
    }
    else if (type == GRID) {
        auto *discrete_cell = dynamic_cast<DiscreteAutomaton*>(cell.get());
        if (discrete_cell && discrete_cell->get_x() >= 0 && discrete_cell->get_x() < width
            && discrete_cell->get_y() >= 0 && discrete_cell->get_y() < height) {
            grid[discrete_cell->get_x()][discrete_cell->get_y()] = std::move(cell);
            current_population++;
        }
    }
}

vector<vector<std::unique_ptr<DiscreteAutomaton>>> Board::get_grid() {
    return grid;
}

void Board::set_grid(vector<vector<std::unique_ptr<DiscreteAutomaton>>> &new_grid) {
    grid = std::move(new_grid);
}

vector<std::unique_ptr<ContinuousAutomaton>> Board::get_continuous() {
    return continuous;
}

void Board::set_continuum(vector<std::unique_ptr<ContinuousAutomaton>> &continuous) {
    this->continuous = std::move(continuous);
}

int Board::get_width() {
    return width;
}

int Board::get_height() {
    return height;
}

int Board::get_current_population() {
    int current_population = 0;
    for (auto &row : grid) {
        for (auto &cell : row) {
            if (cell && cell->get_value() > 0) {
                current_population++;
            }
        }
    }
    return current_population;
}

CellularAutomaton* Board::get_cell(int x, int y) const {
    if (type == GRID && x >= 0 && x < height && y >= 0 && y < width) {
        return grid[x][y].get();
    }
    else if (type == CONTINUOUS && x >= 0 && x < current_population) {
        return continuous[x].get();
    }
    return nullptr;
}

void Board::render () {
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
                DiscreteAutomaton* cell = dynamic_cast<DiscreteAutomaton*>(c);
                if (cell) {
                    //printf("%d ", static_cast<int>(cell->get_value()));
                    cout << static_cast<int>(cell->get_value()) << " ";
                } else {
                    cout << "0 ";
                }
            }
            printf("\n");
        }
    }
}