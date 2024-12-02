cmake_minimum_required(VERSION 3.10)

# Set the project name
project(CellViz)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories (for header files)
include_directories(${PROJECT_SOURCE_DIR}/src)

# Add the main executable
add_executable(CellViz
    src/cellviz.cpp
    src/cells.cpp
    src/board.cpp
    src/data.cpp
    src/visualizer.cpp
    src/visualizer.h
)

# Boost library
find_package(Boost REQUIRED COMPONENTS system)
target_include_directories(CellViz PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(CellViz ${Boost_LIBRARIES})

# SFML library
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
target_include_directories(CellViz PUBLIC ${SFML_INCLUDE_DIR})
target_link_libraries(CellViz sfml-graphics sfml-window sfml-system)

# jsoncpp library
find_package(JsonCpp REQUIRED)
target_link_libraries(CellViz JsonCpp::JsonCpp)

# curl library
find_package(CURL REQUIRED)
target_include_directories(CellViz PUBLIC ${CURL_INCLUDE_DIRS})
target_link_libraries(CellViz ${CURL_LIBRARIES})

# Add a separate executable for data fetching
add_executable(data
    src/fetch_intraday.cpp
    src/data.cpp
    src/data.h
)
target_link_libraries(data ${CURL_LIBRARIES} JsonCpp::JsonCpp pthread ${Boost_LIBRARIES})

# Google Test setup
find_package(GTest REQUIRED)
add_executable(runTests
    tests/tests.cpp
    src/cells.cpp
    src/board.cpp
    src/cells.h
    src/board.h
)
target_link_libraries(runTests GTest::GTest GTest::Main pthread)
target_include_directories(runTests PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_include_directories(runTests PRIVATE /opt/homebrew/include)

# Enable testing
enable_testing()
add_test(NAME runTests COMMAND runTests)
