# CellViz

[![GitHub release](https://img.shields.io/github/v/release/velocitatem/CellViz)](https://github.com/velocitatem/CellViz/releases) [![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT) [![Build Status](https://img.shields.io/github/actions/workflow/status/velocitatem/CellViz/build.yml)](https://github.com/velocitatem/CellViz/actions) [![Language: C++](https://img.shields.io/badge/language-C%2B%2B-%23f34b7d)](https://en.wikipedia.org/wiki/C%2B%2B) [![Platform: Ubuntu](https://img.shields.io/badge/platform-Ubuntu-orange)](https://ubuntu.com/)

Cellular Automata inspired by live-data visualization, designed to handle multidimensional and high-throughput data efficiently.

## Authors
![Contributors](https://contrib.rocks/image?repo=velocitatem/CellViz)

## Requirements

To build and run CellViz, you will need:

- Boost dev libraries (not runtime)
- JsonCpp dev libraries
- Nlohmann Json dev libraries
- CMake
- SFML
- Alpha Vantage API Key

### Installation on Ubuntu

```bash
sudo apt update
sudo apt-get install libboost-all-dev libjsoncpp-dev nlohmann-json3-dev libsfml-dev
```

To use the Alpha Vantage API key, set the environment variable:

```bash
export API_KEY=YOUR_ALPHA_VANTAGE_KEY
```

## Project Structure

```mermaid
sequenceDiagram
    participant User
    participant Main
    participant Board
    participant SmithLife

    User->>Main: Start Application
    Main->>Board: Create Board(Z, Z)
    Main->>CellularLife: Create life cells
    Main->>Board: Add life cells
    loop Update Board
        Main->>CellularLife: Call compute()
        CellularLife->>Board: Update grid
        Board->>Main: Render board
    end
```

## Features

- Visualizes cellular automata for high-throughput, multidimensional data.
- Implements live-data feeds with Alpha Vantage integration.
- Built with C++ and optimized for performance.
- Modular architecture for easy addition of new data types.

## Getting Started

Clone the repository:

```bash
git clone https://github.com/velocitatem/CellViz.git
```

Navigate to the project directory:

```bash
cd CellViz
```

Build the project using CMake:

```bash
mkdir build && cd build
cmake ..
make
```

Run the application:

```bash
./CellViz
```

## Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.
