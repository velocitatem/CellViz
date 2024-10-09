//
// Created by velocitatem on 9/27/24.
//
#include <iostream>
#include  <stdio.h>
#include  <stdlib.h>
#include <vector>

#include "board.h"
#include "cells.h"


using namespace std;
Board initialise_board(int size)
{
    // nxn board of TYPE for SIZE
    Board board(size, size, GRID, 3);
    double ** data;


    // populate board
    string species = "x";
    for (int i = 0 ; i < size; i++) {
        int x = rand() % 100;
        SmithLife *cell = new SmithLife(i, i, x);
        board.add_cell(cell);
    }
    CellularAutomaton * c = board.get_cell(1,1);


    return board;

    int MAX_IT = size, i = 0;
    while (i < MAX_IT) {
        // UPDATE DATA
        SmithLife::compute(board);
        //board = new_board;
        // RENDER
        if (i == MAX_IT-1)
            board.render();

        i+=1;
    }
    return board;
}
