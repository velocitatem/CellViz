//
// Created by velocitatem on 9/27/24.
//
#include <iostream>
#include  <stdio.h>
#include  <stdlib.h>
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "visualizer.h"

#include "board.h"
#include "cells.h"

using namespace std;

using namespace std;
int main(int argc, char *argv[])
{


  int size = 1000;
  sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(size, size), "Cellular automaton visualiser");
  // nxn board of TYPE for SIZE
  Board board(size, size, GRID,size*size);

  string species = "x";
  for (int i = 0 ; i < size; i++) {
      for (int j = 0; j < size; j++) {
          int x = rand() % 2;
          SmithLife *cell = new SmithLife(i, j, x);
          board.add_cell(cell);
      }
  }

  while (window.isOpen()) {
      sf::Event event;
      while (window.pollEvent(event)) {
          if (event.type == sf::Event::Closed)
              window.close();
      }

      SmithLife::compute(board);


      NewVisualizer(board, &window, 1);
      cout << "Rendering" << endl;

  }


}

