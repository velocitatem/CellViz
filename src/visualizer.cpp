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
        cellColor(cCol) {
    cout << "Creating window" << endl;
}

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

            rectangle.setFillColor(color);

            window.draw(rectangle);
        }
    }

    window.display();
}


RainbowVisualiser::RainbowVisualiser(Board &board, int bSize, int cSize, int maxValue, sf::Color bCol, sf::Color cCol, int speed)
        : cycleSpeed(speed),
        Visualiser(board, bSize, cSize, maxValue, bCol, cCol) {
    cout << "Making it rainbow" << endl;
}

void RainbowVisualiser::UpdateBoard() {
    Visualiser::UpdateBoard();
    ColorTuple hsv = ColorTuple::RGBtoHSV(ColorTuple(cellColor.r, cellColor.g, cellColor.b));
    hsv = ColorTuple((hsv.a + cycleSpeed) % 360, hsv.b, hsv.c); // Shift hue
    ColorTuple rgb = ColorTuple::HSVtoRGB(hsv);
    cellColor = sf::Color(rgb.a, rgb.b, rgb.c, 255);
}

ColorTuple::ColorTuple(int a, int b, int c) : a(a), b(b), c(c) {}

ColorTuple ColorTuple::RGBtoHSV(ColorTuple rgb) {
    float r = rgb.a / 255.0f;
    float g = rgb.b / 255.0f;
    float b = rgb.c / 255.0f;

    float maxVal = std::max({r, g, b});
    float minVal = std::min({r, g, b});
    float delta = maxVal - minVal;

    float h = 0.0f;
    float s = 0.0f;
    float v = maxVal;

    if (delta > 0) {
        if (maxVal == r) {
            h = 60 * (fmod(((g - b) / delta), 6));
        } else if (maxVal == g) {
            h = 60 * (((b - r) / delta) + 2);
        } else if (maxVal == b) {
            h = 60 * (((r - g) / delta) + 4);
        }

        if (maxVal > 0) {
            s = delta / maxVal;
        } else {
            s = 0;
        }
    } else {
        h = 0; // Undefined hue
        s = 0;
    }

    if (h < 0) {
        h += 360;
    }

    int H = static_cast<int>(h);            // Hue (0 - 360)
    int S = static_cast<int>(s * 100);      // Saturation (0 - 100)
    int V = static_cast<int>(v * 100);      // Value (0 - 100)

    return ColorTuple(H, S, V);
}

ColorTuple ColorTuple::HSVtoRGB(ColorTuple hsv) {
    float h = hsv.a;            // Hue (0 - 360)
    float s = hsv.b / 100.0f;   // Saturation (0 - 1)
    float v = hsv.c / 100.0f;   // Value (0 - 1)

    float r = 0, g = 0, b = 0;

    if (s == 0) {
        // Grayscale
        r = g = b = v;
    } else {
        float hSector = h / 60.0f;  // Sector (0 - 5)
        int i = static_cast<int>(floor(hSector));  // Sector index
        float f = hSector - i; // Fractional part of hSector

        float p = v * (1.0f - s);
        float q = v * (1.0f - s * f);
        float t = v * (1.0f - s * (1.0f - f));

        // Handle color sector (funky hsv math)
        switch (i) {
            case 0:
                r = v;
                g = t;
                b = p;
                break;
            case 1:
                r = q;
                g = v;
                b = p;
                break;
            case 2:
                r = p;
                g = v;
                b = t;
                break;
            case 3:
                r = p;
                g = q;
                b = v;
                break;
            case 4:
                r = t;
                g = p;
                b = v;
                break;
            default:
                r = v;
                g = p;
                b = q;
                break;
        }
    }

    int R = static_cast<int>(r * 255);
    int G = static_cast<int>(g * 255);
    int B = static_cast<int>(b * 255);

    return ColorTuple(R, G, B);
}