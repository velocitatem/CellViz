cmake_minimum_required(VERSION 3.10)
project(CellViz)

# Set the path to include directories
include_directories(/opt/homebrew/include)

# Add the executable with all the source files
add_executable(CellViz
    src/cellviz.cpp
    src/cells.cpp
    src/fetch_intraday.cpp
)

# Link the required libraries
target_link_libraries(CellViz curl jsoncpp pthread boost_system)
