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


void show_grid(vector<vector<int> > grid, int N) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cout << grid[i][j] << " ";
    }
    cout << endl;
  }

}

using namespace std;
int main(int argc, char *argv[])
{


  // nxn board of TYPE for SIZE
  Board board(5, 5, GRID, 3);
  double ** data;

  // populate board
  string species = "x";
  for (int i = 0 ; i < 3; i++) {
    SmithLife *cell = new SmithLife(i, i, 1.0);
    board.add_cell(cell);
  }
  CellularAutomaton * c = board.get_cell(1,1);


  int MAX_IT = 20, i = 0;
  while (i < MAX_IT) {
    // UPDATE DATA
    SmithLife::compute(&board);
    //board = new_board;
    // RENDER
    board.render();

    i+=1;
  }




}

