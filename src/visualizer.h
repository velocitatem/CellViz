#include <board.h>
#include <SFML/Graphics.hpp>
#ifndef VISUALIZER_H
#define VISUALIZER_H

struct ColorTuple{
    int a, b, c;
    ColorTuple(int a, int b, int c);
    static ColorTuple RGBtoHSV(ColorTuple rgb);
    static ColorTuple HSVtoRGB(ColorTuple rgb);
};

class Visualiser{
public:
    Visualiser();
    Visualiser(Board &board, int bSize, int cSize, int maxValue, sf::Color bCol, sf::Color cCol);
    virtual void UpdateBoard();
    sf::RenderWindow& GetWindow();
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

class RainbowVisualiser : public Visualiser {
public:
    RainbowVisualiser(Board &board, int bSize, int cSize, int maxValue, sf::Color bCol, sf::Color cCol, int speed);
    void UpdateBoard() override;
private:
    int cycleSpeed;
};

#endif //VISUALIZER_H