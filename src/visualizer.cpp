#include <SFML/Graphics.hpp>
#include "cellviz.h"
#include "board.h"
#include "cells.h"
#include "visualizer.h"
#include <math.h>

Visualiser::Visualiser(Board &board, int bSize, int cSize, int maxValue, sf::Color bCol, sf::Color cCol) :
        window(sf::RenderWindow(sf::VideoMode(bSize * cSize, bSize * cSize), "Cellular automaton visualiser")),
        board(board),
        boardSize(bSize),
        cellSize(cSize),
        maxCellValue(maxValue),
        backgroundColor(bCol),
        cellColor(cCol) {}

sf::Color Visualiser::CalculateCellColor(Board& board, int x, int y) {
    CellularAutomaton* cell = board.get_cell(x, y);
    if (!cell) {
        return backgroundColor;
    }
    DiscreteAutomaton* discreteCell = dynamic_cast<DiscreteAutomaton*>(cell);
    if (discreteCell) {
        double value = discreteCell->get_value();
        if (value <= 0) {
            return backgroundColor;
        }
        int intensity = static_cast<int>((value / maxCellValue) * 255);
        return sf::Color(intensity, intensity, intensity);
    }
    return backgroundColor;
}

void Visualiser::UpdateBoard() {
    window.clear(backgroundColor);
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            sf::RectangleShape cellShape(sf::Vector2f(cellSize, cellSize));
            cellShape.setPosition(i * cellSize, j * cellSize);
            cellShape.setFillColor(CalculateCellColor(board, i, j));
            window.draw(cellShape);
        }
    }
    window.display();
}

RainbowVisualiser::RainbowVisualiser(Board &board, int bSize, int cSize, int maxValue, sf::Color bCol, sf::Color cCol, int speed)
        : cycleSpeed(speed),
        Visualiser(board, bSize, cSize, maxValue, bCol, cCol) {}

void RainbowVisualiser::UpdateBoard() {
    window.clear(backgroundColor);
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            sf::RectangleShape cellShape(sf::Vector2f(cellSize, cellSize));
            cellShape.setPosition(i * cellSize, j * cellSize);
            cellShape.setFillColor(CalculateCellColor(board, i, j));
            window.draw(cellShape);
        }
    }
    window.display();
}