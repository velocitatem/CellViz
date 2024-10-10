//
// Created by velocitatem on 10/9/24.
//

#include <board.h>
#include <SFML/Graphics.hpp>
#ifndef VISUALIZER_H
#define VISUALIZER_H

double GetValueFromBoard(Board &board, int x, int y);
void UpdateWindow(Board &board, sf::RenderWindow &window, int size, bool print = false);
void NewVisualizer(Board &board, sf::RenderWindow *window, int cellSize);

#endif //VISUALIZER_H
