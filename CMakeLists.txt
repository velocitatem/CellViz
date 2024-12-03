cmake_minimum_required(VERSION 3.10)

# Set the project name
project(CellViz)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(CellViz
        src/cellviz.cpp
        src/cells.cpp
        src/board.cpp
        src/data.cpp
        src/visualizer.cpp
        src/visualizer.h
)

# Include directories (for header files)
target_include_directories(CellViz PUBLIC ${PROJECT_SOURCE_DIR}/src)

# Link GTK libraries
link_directories(${GTK_LIBRARY_DIRS})
add_definitions(${GTK_CFLAGS_OTHER})

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(CellViz sfml-graphics sfml-window sfml-system)

add_test(NAME runTests COMMAND runTests)