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
  Board board(5, 5, CONTINUOUS, 3);
  double ** data;

  // populate board
  string species = "x";
  for (int i = 0 ; i < 3; i++) {
    board.add_cell(ParticleLife(i,i,species+="x"));
  }


  while (true) {
    // UPDATE DATA
    Board new_board = ParticleLife::compute(&board);
    board = new_board;
    // TODO: render board

  }




}

