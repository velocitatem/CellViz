cmake_minimum_required(VERSION 3.10)

# Set the project name
project(CellViz)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories for source files
include_directories(${PROJECT_SOURCE_DIR}/src)

# Main executable for CellViz
add_executable(CellViz
    src/cellviz.cpp
    src/cells.cpp
    src/board.cpp
    src/data.cpp
    src/visualizer.cpp
    src/visualizer.h
)

# Find Boost
find_package(Boost REQUIRED COMPONENTS system)
target_include_directories(CellViz PUBLIC ${Boost_INCLUDE_DIRS})

# Find GTK+ 3.0
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk+-3.0)
include_directories(${GTK_INCLUDE_DIRS})
target_link_directories(CellViz PRIVATE ${GTK_LIBRARY_DIRS})

# Get linker flags directly from pkg-config
execute_process(
    COMMAND pkg-config --libs gtk+-3.0
    OUTPUT_VARIABLE GTK3_LDFLAGS
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

message(STATUS "GTK3_LDFLAGS: ${GTK3_LDFLAGS}")

# Split the flags into a list
separate_arguments(GTK3_LDFLAGS_LIST UNIX_COMMAND "${GTK3_LDFLAGS}")

# Link libraries
# Removed duplicate link to JsonCpp and fixed linking order
find_library(JSONCPP_LIB jsoncpp HINTS /opt/homebrew/lib)
find_path(JSONCPP_INCLUDE_DIR json/json.h HINTS /opt/homebrew/include)

if(NOT JSONCPP_LIB)
    message(FATAL_ERROR "JsonCpp library not found")
endif()

if(NOT JSONCPP_INCLUDE_DIR)
    message(FATAL_ERROR "JsonCpp include directory not found")
endif()

# Find nlohmann/json
find_path(NLOHMANN_JSON_INCLUDE_DIR nlohmann/json.hpp HINTS /opt/homebrew/include)

if(NOT NLOHMANN_JSON_INCLUDE_DIR)
    message(FATAL_ERROR "nlohmann/json.hpp not found")
endif()

target_include_directories(CellViz PUBLIC ${JSONCPP_INCLUDE_DIR} ${NLOHMANN_JSON_INCLUDE_DIR})
target_link_libraries(CellViz
    ${GTK3_LDFLAGS_LIST}
    ${Boost_LIBRARIES}
    sfml-graphics sfml-window sfml-system
    ${JSONCPP_LIB}
    CURL::libcurl
    "-framework Cocoa"
    "-framework Carbon"
    "-framework CoreGraphics"
)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
target_include_directories(CellViz PUBLIC ${SFML_INCLUDE_DIR})

# Find CURL
find_package(CURL REQUIRED)

# Data fetching executable
add_executable(data
    src/fetch_intraday.cpp
    src/data.cpp
    src/data.h
)
target_link_libraries(data
    CURL::libcurl
    ${JSONCPP_LIB}
    pthread
    ${Boost_LIBRARIES}
)

# Google Test setup
find_package(GTest REQUIRED)
add_executable(runTests
    tests/tests.cpp
    src/cells.cpp
    src/board.cpp
    src/cells.h
    src/board.h
)

# Include nlohmann/json for tests
target_include_directories(runTests PUBLIC ${PROJECT_SOURCE_DIR}/src ${GTEST_INCLUDE_DIRS} ${NLOHMANN_JSON_INCLUDE_DIR})
target_link_libraries(runTests GTest::GTest GTest::Main pthread)

# Enable testing
enable_testing()
add_test(NAME runTests COMMAND runTests)
