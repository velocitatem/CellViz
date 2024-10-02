cmake_minimum_required(VERSION 3.10)
project(CellViz)

add_executable(CellViz src/cellviz.cpp src/cells.cpp
        src/board.cpp
        src/board.h)