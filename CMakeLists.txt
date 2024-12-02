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

# Include directories (for header files)
target_include_directories(CellViz PUBLIC ${PROJECT_SOURCE_DIR}/src)

# libboost
find_package(Boost REQUIRED COMPONENTS system)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk+-3.0)

# Include GTK headers
include_directories(${GTK_INCLUDE_DIRS})

# Link GTK libraries
link_directories(${GTK_LIBRARY_DIRS})
add_definitions(${GTK_CFLAGS_OTHER})


# SFML library
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(CellViz sfml-graphics sfml-window sfml-system curl jsoncpp pthread ${Boost_LIBRARIES} ${GTK_LIBRARIES})


# Add a separate executable for data fetching
add_executable(data
    src/fetch_intraday.cpp
    src/data.cpp
    src/data.h
)
target_link_libraries(data ${CURL_LIBRARIES} JsonCpp::JsonCpp pthread ${Boost_LIBRARIES})

# Google Test setup
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add test executable
add_executable(runTests
        tests/tests.cpp
        src/cells.cpp
        src/board.cpp
        src/cells.h
        src/board.h
        upstream/main
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
