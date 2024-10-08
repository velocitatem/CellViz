cmake_minimum_required(VERSION 3.10)

# Set the project name
project(CellViz)

include_directories(/opt/homebrew/include)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(CellViz
        src/cellviz.cpp
        src/cells.cpp
        src/board.cpp
        src/fetch_intraday.cpp
)

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
        src/cells.h src/board.h
        src/fetch_intraday.cpp)
target_link_libraries(runTests GTest::GTest GTest::Main pthread)
target_include_directories(runTests PUBLIC ${PROJECT_SOURCE_DIR}/src)


# Link the required libraries
target_link_libraries(CellViz curl jsoncpp pthread boost_system)

# Enable tests
enable_testing()
add_test(NAME runTests COMMAND runTests)

