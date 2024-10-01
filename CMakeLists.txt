cmake_minimum_required(VERSION 3.10)
project(CellViz)

add_executable(CellViz src/cellviz.cpp src/cells.cpp)

set(CMAKE_CXX_STANDARD 17)

include_directories(/opt/homebrew/Cellar/jsoncpp/1.9.6/include)

# Add the executable
add_executable(CellViz src/data.cpp)

# Link the JSON library
target_link_libraries(CellViz jsoncpp)