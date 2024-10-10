//
// Created by velocitatem on 10/9/24.
//

#include <board.h>
#include <SFML/Graphics.hpp>
#ifndef VISUALIZER_H
#define VISUALIZER_H

class Visualiser{
public:
    Visualiser(Board &board, int bSize, int cSize, int maxValue, sf::Color bCol, sf::Color cCol);
    void UpdateBoard();
    sf::RenderWindow& GetWindow(){
        return window;
    }
    sf::Color CalculateCellColor(Board& board, int x, int y);
protected:
    Board &board;
    sf::RenderWindow window;
    int boardSize;
    int cellSize;
    int maxCellValue;
    sf::Color backgroundColor;
    sf::Color cellColor;
};

#endif //VISUALIZER_H
