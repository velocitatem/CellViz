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
        src/visualiser.cpp
        src/visualizer.h
)

# Include directories (for header files)
target_include_directories(CellViz PUBLIC ${PROJECT_SOURCE_DIR}/src)

# libboost
find_package(Boost REQUIRED COMPONENTS system)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(CellViz sfml-graphics sfml-window sfml-system curl jsoncpp pthread ${Boost_LIBRARIES})


add_executable(data src/fetch_intraday.cpp src/data.cpp src/data.h) # TODO: move to individual library
target_link_libraries(data curl jsoncpp pthread ${Boost_LIBRARIES})

# Find and link Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add test executable
add_executable(runTests
        tests/tests.cpp
        src/cells.cpp
        src/board.cpp
        src/cells.h src/board.h)

target_link_libraries(runTests GTest::GTest GTest::Main pthread)
target_include_directories(runTests PUBLIC ${PROJECT_SOURCE_DIR}/src)

# Enable tests
enable_testing()
add_test(NAME runTests COMMAND runTests)