#include <complex>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <random>
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "visualizer.h"
#include "board.h"
#include "cells.h"
#include <gtk/gtk.h>

using json = nlohmann::json;

using namespace std;

void save_frame(const sf::RenderWindow &window, int frame_number) {
    sf::Texture texture;
    texture.create(window.getSize().x, window.getSize().y);
    sf::Image screenshot = texture.copyToImage();

    std::ostringstream filename;
    filename << "frame_" << std::setw(5) << std::setfill('0') << frame_number << ".png";
    screenshot.saveToFile(filename.str());
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *windowg = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(windowg), "CellViz!");
    gtk_window_set_default_size(GTK_WINDOW(windowg), 400, 300);

    g_signal_connect(windowg, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *label = gtk_label_new("CellViz - Cellular Automata Visualizer");

    // use mean or median toggle
    GtkWidget *mean_median_toggle = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(mean_median_toggle), "Mean");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(mean_median_toggle), "Median");
    gtk_combo_box_set_active(GTK_COMBO_BOX(mean_median_toggle), 0);

    // add all
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(windowg), vbox);
    gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), mean_median_toggle, TRUE, TRUE, 0);

    // add button to close the window
    GtkWidget *button = gtk_button_new_with_label("Run Simulation");
    g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_destroy), windowg);
    gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, TRUE, 0);

    gtk_widget_show_all(windowg);
    gtk_main();

    // CLI SECTION:
    /// help message
    /// arguments:
    //  - json_file (string) - the json file to read from
    /// - output.mp4 (string) - the output file to write to (if not specified does nto write to file)
    /// - life=(smith|basic) - the type of life to use
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <json_file> [output.mp4] [life=(smith|basic)]" << endl;
        return 1;
    }

    // check json file
    string json_file_path = argv[1];
    if (json_file_path.find(".json") == string::npos) {
        cout << "Invalid JSON file" << endl;
        return 1;
    }

    // Read JSON file
    std::ifstream json_file(json_file_path);
    json j;
    json_file >> j;

    // Extract Time Series Data
    int count = 0;
    auto time_series = j["Time Series (Daily)"];
    vector<double> prices;
    for (auto& [key, value] : time_series.items()) {
        prices.push_back(stod(value["4. close"].get<string>()));
        count++;
    }

    // shuffle(prices.begin(), prices.end(), std::mt19937(std::random_device()())); // suggested by intelligence

    double sum = 0;
    double mean = 0, median = 0;
    for (const auto& price : prices) {
        sum += price;
    }
    mean = sum / count;
    sort(prices.begin(), prices.end());
    if (count % 2 == 0) {
        median = (prices[count / 2 - 1] + prices[count / 2]) / 2;
    } else {
        median = prices[count / 2];
    }

    int size = count / 8;
    Board board(size, size, GRID, 3);
    auto start = prices.begin();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            double value = *start;
            auto cell = std::make_unique<SmithLife>(i, j, value < mean ? 0 : 1);
            board.add_cell(std::move(cell));
            if (start == prices.end())
                start = prices.begin();
            start++;
        }
    }

    sf::RenderWindow window(sf::VideoMode(size * 10, size * 10), "Cellular Automaton");
    Visualiser visualiser(board, size, 10, 1, sf::Color::Black, sf::Color::White);

    int frame_number = 0;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        visualiser.UpdateBoard();
        save_frame(window, frame_number++);
    }

    if (argc >= 3) {
        string output_file = argv[2];
        if (output_file.find(".mp4") != string::npos) {
            // Code to convert frames to video
        }
    }

    return 0;
}