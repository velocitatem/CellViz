cmake_minimum_required(VERSION 3.20)

# Set the project name
project(CellViz CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set CMake policy to handle Boost deprecation
cmake_policy(SET CMP0167 NEW)

# Find required packages
find_package(JsonCpp REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)
find_package(PkgConfig REQUIRED)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
find_package(CURL REQUIRED)
find_package(GTest REQUIRED)

# PKG-CONFIG for GTK
pkg_check_modules(GTK REQUIRED gtk+-3.0)

# Locate nlohmann/json header
find_path(NLOHMANN_JSON_INCLUDE_DIR nlohmann/json.hpp 
    HINTS 
    /opt/homebrew/include 
    /usr/local/include 
    /usr/include 
    /opt/homebrew/opt/nlohmann-json/include
)

if(NOT NLOHMANN_JSON_INCLUDE_DIR)
    message(FATAL_ERROR "nlohmann/json.hpp not found")
endif()

# Include directories
include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${Boost_INCLUDE_DIRS}
    ${GTK_INCLUDE_DIRS}
    ${SFML_INCLUDE_DIR}
    ${JSONCPP_INCLUDE_DIRS}
    ${NLOHMANN_JSON_INCLUDE_DIR}
)

# Link directories
link_directories(${GTK_LIBRARY_DIRS})

# Main executable
add_executable(CellViz
    src/cellviz.cpp
    src/cells.cpp
    src/board.cpp
    src/data.cpp
    src/visualizer.cpp
    src/visualizer.h
)

# Linking libraries for the main executable
target_link_libraries(CellViz
    ${GTK_LIBRARIES}
    ${Boost_LIBRARIES}
    sfml-graphics
    sfml-window
    sfml-system
    CURL::libcurl
    JsonCpp::JsonCpp
    "-framework Cocoa"
    "-framework Carbon"
    "-framework CoreGraphics"
)

# Data fetching executable
add_executable(data
    src/fetch_intraday.cpp
    src/data.cpp
    src/data.h
)

target_link_libraries(data
    CURL::libcurl
    JsonCpp::JsonCpp
    pthread
    ${Boost_LIBRARIES}
)

# Testing executable
add_executable(runTests
    tests/tests.cpp
    src/cells.cpp
    src/board.cpp
    src/cells.h
    src/board.h
)

# Include directories for testing
target_include_directories(runTests PRIVATE 
    ${PROJECT_SOURCE_DIR}/src
    ${GTEST_INCLUDE_DIRS}
    ${NLOHMANN_JSON_INCLUDE_DIR}
)

# Linking libraries for testing
target_link_libraries(runTests 
    GTest::gtest 
    GTest::gtest_main
    pthread
)

# Enable testing
enable_testing()
add_test(NAME runTests COMMAND runTests)
