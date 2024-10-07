cmake_minimum_required(VERSION 3.10)

# Set the project name
project(CellViz)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)   # Or 11/14/20, depending on your needs
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(CellViz
        src/cellviz.cpp
        src/cells.cpp
        src/board.cpp
        tests/tests.cpp
)

# Include directories (for header files)
target_include_directories(CellViz PUBLIC ${PROJECT_SOURCE_DIR}/src)
