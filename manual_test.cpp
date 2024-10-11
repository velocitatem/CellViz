#include <iostream>
#include <cassert>
#include "board.h"

void testBoardConstructor() {
    Board b;
    std::cout << "Running testBoardConstructor..." << std::endl;
    assert(b.get_current_population() == 0);  // Sample test
    std::cout << "testBoardConstructor passed." << std::endl;
}

int main() {
    std::cout << "Starting tests..." << std::endl;
    testBoardConstructor();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
