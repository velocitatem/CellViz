//
// Created by velocitatem on 9/27/24.
// Added documentation - Aswin
//

/*!
 * @mainpage CellViz Project Documentation
 *
 * @section intro_sec Introduction
 *
 * Welcome to the **CellViz** documentation. This project is an advanced visualization tool for cellular automata models. It allows the simulation and visualization of various types of cellular automata, including both discrete (grid-based) and continuous systems.
 *
 * The primary goal of CellViz is to provide a framework to study complex systems through simple local interactions that give rise to emergent global behavior. Cellular Automata have applications in fields like physics, biology, economics, and computer science, making them a useful tool for simulating real-world systems.
 *
 * @section automata_sec About Cellular Automata
 *
 * Cellular automata (CA) are models consisting of a grid of cells, each of which can exist in a finite number of states. The state of each cell evolves based on a set of rules, often influenced by its neighbors. This leads to emergent behavior, where complex global patterns form from simple local rules.
 *
 * ### Types of Cellular Automata
 * - **Discrete Automata (Grid-based)**: The cells are arranged in a grid, and each cell's state depends on its neighbors. Examples include Conway's Game of Life.
 * - **Continuous Automata**: These are not restricted to discrete states or grid locations, providing a more fluid simulation environment.
 *
 * Below are some visualizations of typical cellular automata:
 * 
 * ![Continuous Cellular Automaton](images/continuous_automaton.png)
 *
 * @section usage_sec Usage
 *
 * CellViz can be executed from the command line with different modes:
 *
 * ```
 * ./data 
 * ./CellViz <json_file> [output.mp4] [life=(smith|basic)]
 * ```
 *
 * - `<json_file>`: Configuration file specifying the initial state.
 * - `[output.mp4]`: Optional argument to specify the output video file.
 * - `[life=(smith|basic)]`: Specifies which type of life simulation to use.
 *
 * @section github_sec GitHub Repository
 *
 * You can find the source code, report issues, and contribute to the project on [GitHub](https://github.com/velocitatem/CellViz).
 *
 * @section features_sec Features
 *
 * - **Modular Design**: The project consists of various types of cellular automata.
 * - **Visualization**: Supports both real-time rendering and output to video.
 * - **Extensible Framework**: Allows adding new types of automata by extending the existing classes.
 *
 * @section directory_sec Directory Structure
 *
 * - **src**: Contains all source code files, including implementation of different automata (`board.cpp`, `cells.cpp`, etc.).
 * - **tests**: Contains unit tests to verify the functionality of the project.
 * - **demo**: Includes demo files to visualize examples.
 *
 * @section contact_sec Contact and Contributions
 *
 * We welcome contributions, feature suggestions, and bug reports. You can participate by creating issues or pull requests on the [GitHub repository](https://github.com/velocitatem/CellViz).
 *
 * @section acknowledgements_sec Acknowledgements
 *
 * This project was developed by **B Flat**. It is inspired by the principles of cellular automata, originally conceived by **John von Neumann** and **Stanislaw Ulam**.
 */


#include "cells.h"
#include <fstream>
#include <map>

using json = nlohmann::json;

/**
 * @class ParticleLife
 * @brief Represents a type of continuous cellular automaton called ParticleLife.
 */

/** @brief Default constructor for ParticleLife. */
ParticleLife::ParticleLife() : x(0), y(0), species("") {}

/** 
 * @brief Parameterized constructor for ParticleLife.
 * 
 * @param x The x-coordinate of the ParticleLife cell.
 * @param y The y-coordinate of the ParticleLife cell.
 * @param species The species identifier for the ParticleLife cell.
 */
ParticleLife::ParticleLife(int x, int y, string species) : x(x), y(y), species(species) {}

/**
 * @brief Computes the state of the board with ParticleLife rules.
 * 
 * @param board Pointer to the Board instance.
 * @return A modified Board instance.
 */
Board ParticleLife::compute(Board *board) {
    map<string, ContinuousAutomaton> cellular_automaton;
    vector<ContinuousAutomaton*> all = board->get_continuous();
    for (int i = 0; i < board->get_current_population(); i += 1) {
        ContinuousAutomaton cell = *all[i];
        //cellular_automaton.insert(make_pair(cell.species, CellularAutomaton()));
    }
    return *board;
}

/**
 * @class DiscreteAutomaton
 * @brief Represents a type of cellular automaton called DiscreteAutomaton.
 */

/** @brief Default constructor for DiscreteAutomaton. */
DiscreteAutomaton::DiscreteAutomaton() : x(0), y(0), value(0) {}

/**
 * @brief Parameterized constructor for DiscreteAutomaton.
 * 
 * @param x The x-coordinate of the cell.
 * @param y The y-coordinate of the cell.
 * @param value The value of the cell.
 */
DiscreteAutomaton::DiscreteAutomaton(int x, int y, double value) : x(x), y(y), value(value) {}

/**
 * @brief Copy constructor for DiscreteAutomaton.
 * 
 * @param cell The DiscreteAutomaton object to copy.
 */
DiscreteAutomaton::DiscreteAutomaton(const DiscreteAutomaton &cell) {
    x = cell.x;
    y = cell.y;
    value = cell.value;
}

/**
 * @brief Sets the x-coordinate of the DiscreteAutomaton.
 * 
 * @param x The new x-coordinate.
 */
void DiscreteAutomaton::set_x(int x) { this->x = x; }

/**
 * @brief Sets the y-coordinate of the DiscreteAutomaton.
 * 
 * @param y The new y-coordinate.
 */
void DiscreteAutomaton::set_y(int y) { this->y = y; }

/**
 * @brief Sets the value of the DiscreteAutomaton.
 * 
 * @param value The new value.
 */
void DiscreteAutomaton::set_value(double value) { this->value = value; }

/**
 * @brief Equality operator for DiscreteAutomaton.
 * 
 * @param cell The DiscreteAutomaton to compare.
 * @return true if both cells are equal, false otherwise.
 */
bool DiscreteAutomaton::operator==(const DiscreteAutomaton &cell) const {
    const double EPSILON = 1e-9;
    return x == cell.x && y == cell.y && std::abs(value - cell.value) < EPSILON;
}

/**
 * @class SmithLife
 * @brief Represents a type of cellular automaton called SmithLife.
 */

/** 
 * @brief Parameterized constructor for SmithLife.
 * 
 * @param x The x-coordinate of the cell.
 * @param y The y-coordinate of the cell.
 * @param value The value of the cell.
 */
SmithLife::SmithLife(int x, int y, double value) : x(x), y(y), value(value) {}

/** @brief Gets the x-coordinate of the SmithLife cell. */
int SmithLife::get_x() { return x; }

/** @brief Gets the y-coordinate of the SmithLife cell. */
int SmithLife::get_y() { return y; }

/** @brief Gets the value of the SmithLife cell. */
double SmithLife::get_value() { return value; }

/**
 * @brief Sets the value of the SmithLife cell.
 * 
 * @param value The new value.
 */
void SmithLife::set_value(double value) {
    this->value = value;
}

/** @brief Destructor for SmithLife. */
SmithLife::~SmithLife() {}

/**
 * @brief Computes the next state of the Board based on SmithLife rules.
 * 
 * @param board Reference to the Board instance.
 */
void SmithLife::compute(Board &board) {
    std::vector<std::vector<DiscreteAutomaton*>> grid = board.get_grid();
    for (int i = 0; i < board.get_height(); i++) {
        for (int j = 0; j < board.get_width(); j++) {
            DiscreteAutomaton *cell = dynamic_cast<DiscreteAutomaton*>(board.get_cell(i, j));
            if (cell) {
                int neighbors[8][2] = {
                    {i-1, j-1}, {i-1, j}, {i-1, j+1},
                    {i, j-1}, {i, j+1},
                    {i+1, j-1}, {i+1, j}, {i+1, j+1}
                };
                int count = 0;
                for (int k = 0; k < 8; k++) {
                    int x = neighbors[k][0];
                    int y = neighbors[k][1];
                    if (x >= 0 && x < board.get_width() && y >= 0 && y < board.get_height()) {
                        DiscreteAutomaton *neighbor = dynamic_cast<DiscreteAutomaton*>(board.get_cell(x, y));
                        if (neighbor && neighbor->get_value() > 0) {
                            count++;
                        }
                    }
                }
                if (cell->get_value() == 1) {
                    if (count < 2 || count > 3) { // we see if we kill the cell
                        auto pointer_to_cell = grid[i][j];
                        auto smith_life = dynamic_cast<SmithLife*>(pointer_to_cell);
                        smith_life->set_value(0);
                    }
                } else {
                    if (count == 3) {
                        auto pointer_to_cell = grid[i][j];
                        auto smith_life = dynamic_cast<SmithLife*>(pointer_to_cell);
                        smith_life->set_value(1);
                    }
                }
                // to make things interesting, we add a 5% chance of a cell dying
                if (rand() % 100 < 5) {
                    auto pointer_to_cell = grid[i][j];
                    auto smith_life = dynamic_cast<SmithLife*>(pointer_to_cell);
                    smith_life->set_value(0);
                }
            }
        }
    }
    board.set_grid(grid);
}

/**
 * @class BasicLife
 * @brief Represents a type of cellular automaton called BasicLife.
 */

/**
 * @brief Parameterized constructor for BasicLife.
 * 
 * @param x The x-coordinate of the cell.
 * @param y The y-coordinate of the cell.
 * @param value The value of the cell.
 */
BasicLife::BasicLife(int x, int y, double value) : x(x), y(y), value(value) {}

/** @brief Gets the x-coordinate of the BasicLife cell. */
int BasicLife::get_x() { return x; }

/** @brief Gets the y-coordinate of the BasicLife cell. */
int BasicLife::get_y() { return y; }

/** @brief Gets the value of the BasicLife cell. */
double BasicLife::get_value() { return value; }

/**
 * @brief Computes the next state of the Board based on BasicLife rules.
 * 
 * @param board Pointer to the Board instance.
 */
void BasicLife::compute(Board *board) {
    std::vector<std::vector<DiscreteAutomaton*>> grid = board->get_grid();
    for (int i = 0; i < board->get_height(); i++) {
        for (int j = 0; j < board->get_width(); j++) {
            BasicLife *cell = dynamic_cast<BasicLife*>(board->get_cell(i, j));
            if (cell) {
                double new_value = cell->get_value() + 1;
                cell = new BasicLife(i, j, new_value);
                grid[i][j] = cell;
            }
        }
    }
    board->set_grid(grid);
}
