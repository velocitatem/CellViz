cmake_minimum_required(VERSION 3.10)

# Set the project name
project(CellViz)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include sfml
set(SFML_DIR "C:/Program Files/SFML-2.6.1/")
include_directories(${SFML_DIR}/include)
link_directories(${SFML_DIR}/lib)
add_definitions(-DSFML_STATIC)

# Add the executable
add_executable(CellViz
        src/cellviz.h
        src/cells.cpp
        src/board.cpp
        src/visualiser/visualiser.cpp
)

target_link_libraries(Cellviz sfml-graphics sfml-audio sfml-system sfml-window)

# Include directories (for header files)
target_include_directories(CellViz PUBLIC ${PROJECT_SOURCE_DIR}/src)

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