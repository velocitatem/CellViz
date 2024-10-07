cmake_minimum_required(VERSION 3.10)
project(CellViz)

set(JSONCPP_INCLUDE_DIR "/opt/homebrew/Cellar/jsoncpp/1.9.6/include" CACHE PATH "Path to JsonCpp include directory")
include_directories(${JSONCPP_INCLUDE_DIR})
add_executable(CellViz src/cellviz.cpp src/cells.cpp src/data.cpp)
include_directories(/opt/homebrew/Cellar/jsoncpp/1.9.6/include)

# Add the executable
add_executable(CellViz src/data.cpp)

# Link the JSON library
target_link_libraries(CellViz jsoncpp)