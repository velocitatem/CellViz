#include <SFML/Graphics.hpp>

#include "backend/cellviz.h"
#include "backend/board.h"
#include "backend/cells.h"

double GetValueFromBoard(Board &board, int x, int y){
    CellularAutomaton* c = board.get_cell(x, y);
    if (!c) {
        return 0;
    }
    DiscreteAutomaton* cell = dynamic_cast<DiscreteAutomaton*>(c);
    if (cell) {
        return static_cast<int>(cell->get_value());
    } else {
        return 0;
    }
}

void UpdateWindow(Board &board, sf::RenderWindow &window, int size, bool print = false){
    print = size < 10;
    double maxValue = 1000;

    //only draw where there are cells
    window.clear(sf::Color(0,0,0));

    for (int x = 0; x < size; ++x) {
        for (int y = 0; y < size; ++y) {
            double value = GetValueFromBoard(board, x, y);

            if (value <= 0) continue;

            int c = min(value/maxValue, 1.0) * 255.0;

            if(print) printf("(%d, %d): %f -> %d ", x, y, value, c);

            sf::Color colour(0, 0, c);
            // Set the pixel color using a small rectangle
            sf::RectangleShape pixel(sf::Vector2f(1, 1)); // 1x1 pixel
            pixel.setPosition(static_cast<float>(x), static_cast<float>(y));
            pixel.setFillColor(colour);
            window.draw(pixel);
        }
    }
    if(print)printf("\n");
    window.display();
}

int main() {
    int size = 800;

    Board board = initialise_board(size);

    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(size, size), "Cellular automaton visualiser");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        SmithLife::compute(&board);
        UpdateWindow(board, window, size);
    }
    return 0;
}