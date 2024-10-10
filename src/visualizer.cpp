#include <SFML/Graphics.hpp>
#include "cellviz.h"
#include "board.h"
#include "cells.h"

void NewVisualizer(Board &board, sf::RenderWindow *window, int cellSize) {
    window->clear(sf::Color::Black);

    int boardHeight = board.get_height();
    int boardWidth = board.get_width();

    for (int x = 0; x < boardHeight; ++x) {
        for (int y = 0; y < boardWidth; ++y) {
            DiscreteAutomaton *cell = dynamic_cast<DiscreteAutomaton*>(board.get_cell(x, y));
            if (!cell) continue;

            double value = cell->get_value();
            if (value <= 0) continue;

            int colorIntensity = static_cast<int>(value * 255.0);
            sf::Color color(0, colorIntensity * 0.5, colorIntensity);

            sf::RectangleShape rectangle(sf::Vector2f(static_cast<float>(cellSize), static_cast<float>(cellSize)));
            rectangle.setPosition(static_cast<float>(y * cellSize), static_cast<float>(x * cellSize));
            rectangle.setFillColor(color);

            window->draw(rectangle);
        }
    }
    window->display();
}