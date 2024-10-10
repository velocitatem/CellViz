#include <SFML/Graphics.hpp>
#include "cellviz.h"
#include "board.h"
#include "cells.h"
#include "visualizer.h"


sf::Color Visualiser::CalculateCellColor(Board& board, int x, int y) {
    sf::Color nullColor = sf::Color(0,0,0,0);

    DiscreteAutomaton *cell = dynamic_cast<DiscreteAutomaton*>(board.get_cell(x / cellSize, y / cellSize));
    if (!cell) return nullColor;

    double value = cell->get_value();
    if (value <= 0) return nullColor;

    double colorIntensity = min(1.0, value / maxCellValue);
    return sf::Color(cellColor.r * colorIntensity, cellColor.g * colorIntensity, cellColor.b * colorIntensity, 255);
}

void Visualiser::UpdateBoard() {
    window.clear(backgroundColor);

    for (int x = 0; x < boardSize * cellSize; ++x) {
        for (int y = 0; y < boardSize * cellSize; ++y) {
            sf::Color color = CalculateCellColor(board, x, y);

            if(color.a == 0) continue;

            sf::RectangleShape rectangle(sf::Vector2f(cellSize, cellSize));
            rectangle.setPosition(y * cellSize, x * cellSize);

            //sf::Color(cellColor.r, cellColor.g, cellColor.b, 255);
            rectangle.setFillColor(color);

            window.draw(rectangle);
        }
    }

    window.display();
}

Visualiser::Visualiser(Board &board, int bSize, int cSize, int maxValue, sf::Color bCol, sf::Color cCol) :
    window(sf::RenderWindow(sf::VideoMode(bSize * cSize, bSize * cSize), "Cellular automaton visualiser")),
    board(board),
    boardSize(bSize),
    cellSize(cSize),
    maxCellValue(maxValue),
    backgroundColor(bCol),
    cellColor(cCol) {
    cout << "Creating window" << endl;
}