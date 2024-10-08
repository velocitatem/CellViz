//
// Created by velocitatem on 9/27/24.
//
#include <fstream>
#include <iostream>
#include  <stdio.h>
#include  <stdlib.h>
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "visualizer.h"
#include "board.h"
#include "cells.h"

using json = nlohmann::json;

using namespace std;
int main(int argc, char *argv[]) {

    // Read JSON file
    std::ifstream json_file("output.json");
    json j;
    json_file >> j;

    // Extract Time Series Data
    double count = 0;
    auto time_series = j["Time Series (5min)"];
    vector<double> prices;
    for (auto& [key, value] : time_series.items()) {
        double close_price = stod(value["4. close"].get<string>());
        double open_price = stod(value["1. open"].get<string>());
        double high_price = stod(value["2. high"].get<string>());
        double low_price = stod(value["3. low"].get<string>());
        // because we are low on data and the stock market does not have as much viable different data each day
        // we will use the same data for each day (different sub-data)
        prices.push_back(close_price);
        prices.push_back(open_price);
        prices.push_back(high_price);
        prices.push_back(low_price);
        count += 4;
    }

    random_shuffle(prices.begin(), prices.end());
    // for more interesting results

    double sum = 0;
    double mean = 0;
    for (const auto& price : prices) {
        sum += price;
    }
    mean = sum / count;

    int size = count / 2;
    cout << "Size: " << size << endl;

    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(size, size), "Cellular automaton visualiser");
    Board board(size, size, GRID,size*size);

    string species = "x";
    int c = 0;
    for (int i = 0 ; i < size; i++) {
        for (int j = 0; j < size; j++) {
            SmithLife *cell = new SmithLife(i, j, prices[c] < mean ? 0 : 1);
            board.add_cell(cell);
            c+=1;
        }
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        try {
            SmithLife::compute(board);
        } catch (exception &e) {
            cout << e.what() << endl;
        }
        NewVisualizer(board, &window, 1);
        cout << "Rendering" << endl;
    }

}