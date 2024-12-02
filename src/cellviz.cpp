//
// Created by velocitatem on 9/27/24.
//
#include <complex>
#include <fstream>
#include <iostream>
#include  <stdio.h>
#include  <stdlib.h>
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
    texture.update(window);
    sf::Image screenshot = texture.copyToImage();

    std::ostringstream filename;
    filename << "frame_" << std::setw(5) << std::setfill('0') << frame_number << ".png";
    screenshot.saveToFile(filename.str());
}

int main(int argc, char *argv[])
{


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

    // chekc json file
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

    //shuffle(prices.begin(), prices.end(), std::mt19937(std::random_device()())); // suggested by inteligence

    double sum = 0;
    double mean = 0, median = 0;
    for (const auto& price : prices) sum += price; //
    mean = sum / count;
    sort(prices.begin(), prices.end());
    if (count % 2 == 0) {
        median = (prices[count / 2 - 1] + prices[count / 2]) / 2;
    } else {
        median = prices[count / 2];
    }


    int size = count / 8;


    Board board(size, size, GRID,size*size);
    Visualiser visualiser(board, size, 4, 1, sf::Color::Black, sf::Color::White);
    sf::RenderWindow& window = visualiser.GetWindow();

    string species = "x";
    // create a vector itterator
    auto start = prices.begin();
    int mean_or_median_value = 0;
    if (mean_or_median_value == 0) {
        mean_or_median_value = mean;
    } else {
        mean_or_median_value = median;
    }

    for (int i = 0 ; i < size; i++) {
        for (int j = 0; j < size; j++) {
            double value = *start;
            SmithLife *cell = new SmithLife(i, j, value < mean_or_median_value? 0 : 1); // we make it 1 if it did better than the mean
            board.add_cell(cell); // add to the board..
            if (start == prices.end())
                start = prices.begin();
            start++;
        }
    }
    visualiser.UpdateBoard();

    int frame = 0;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) { // so that we can exit the program
            if (event.type == sf::Event::Closed)
                window.close();
        }
        try {
            SmithLife::compute(board); // compute the board according to what we want to run
        } catch (exception &e) {
            cout << e.what() << endl;
        }

        visualiser.UpdateBoard();

        save_frame(window, frame++);

        // board.render() for CLI rendering
        cout << "Rendering" << endl;
        // now for timeouts
        //sf::sleep(sf::milliseconds(1000));
        // if less than 5 live cells, break
        if (board.get_current_population() < 5) {
            break;
        }

    }

    if (argc < 3) {
        return 0;
    }
    // check if output file is specified
    string output_file = argv[2];
    if (output_file.find(".mp4") == string::npos) {
        cout << "Invalid output file" << endl;
        return 1;
    }

    try {
        system("ffmpeg -version");
    } catch (exception &e) {
        cout << "FFMPEG is not installed" << endl;
        return 0;
    }
    //system(("ffmpeg -framerate 10 -i frame_%05d.png -c:v libx264 -pix_fmt yuv420p " + output_file).c_str());
    system("rm frame_*.png");

    return 0;


}