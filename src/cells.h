//
// Created by velocitatem on 9/27/24.
//

#include <string>
#ifndef CELLS_H
#define CELLS_H


#include "board.h"

class Board;
using namespace std;

class CellularAutomaton {
    static void compute(Board *board);
};

class ParticleLife : public CellularAutomaton {
public:
    ParticleLife(int x, int y, string species); //TODO: Color
    int get_x();
    int get_y();
    string get_species();
    static Board compute(Board *board);
private:
    int x, y;
    string species;
};

class Lenia : public CellularAutomaton {
    // TODO
};





#endif //CELLS_H
