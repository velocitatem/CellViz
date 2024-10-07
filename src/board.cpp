//
// Created by velocitatem on 10/2/24.
//

#include "board.h"

#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <map>


using namespace std;

Board::Board(int width, int height, BoardType type, int population = 0) :
width(width), height(height), type(type), population(population), current_population(0) {
    if (type == GRID) {
        grid = (DiscreteAutomaton**)malloc(sizeof(DiscreteAutomaton) * height);
        for (int i = 0; i < height; i++) {
            grid[i] = (DiscreteAutomaton*)malloc(sizeof(DiscreteAutomaton) * width);
        }

    }
    else if (type == CONTINUOUS) {
        continuous = (ContinuousAutomaton*)malloc(sizeof(ContinuousAutomaton) * population);

    }
}

Board::~Board() {
}


void Board::add_cell(CellularAutomaton *cell) {
    if (type == CONTINUOUS) {
        ContinuousAutomaton *continuous = dynamic_cast<ContinuousAutomaton*>(cell);
        continuous[current_population] = *continuous;
        current_population += 1;
    }
    else if (type == GRID) {
        DiscreteAutomaton *discrete = dynamic_cast<DiscreteAutomaton*>(cell);
        if (discrete) {
            grid[discrete->get_x()][discrete->get_y()] = *discrete;
            current_population += 1;
        }
    }


}


ContinuousAutomaton *Board::get_continuous() {
    return continuous;
}

DiscreteAutomaton **Board::get_grid() {
    return grid;
}




int Board::get_current_population() {
    return current_population;
}



void Board::render() {
    if (type == CONTINUOUS) {
        for (int i = 0; i < population; i++) {
            CellularAutomaton automaton = continuous[i];

        }
    }
    else if (type == GRID) {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                CellularAutomaton *automaton = &grid[i][j];
                DiscreteAutomaton *discrete = dynamic_cast<DiscreteAutomaton*>(automaton);
                printf("%f", discrete->get_value());

            }
        }
    }

}
