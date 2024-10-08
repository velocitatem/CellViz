//
// Created by velocitatem on 10/4/24.
//


#include <gtest/gtest.h>
#include <board.h>

TEST(test1, test1) {
    // A test to test tests
    EXPECT_EQ(1, 1);
}


TEST(SmithLifeTest, Initialization) {
    SmithLife cell(0, 0, 1.0);
    EXPECT_EQ(cell.get_x(), 0);
    EXPECT_EQ(cell.get_y(), 0);
    EXPECT_EQ(cell.get_value(), 1.0);
}

TEST(BoardTest, AddCell) {
    Board board(5, 5, GRID, 3);
    SmithLife *cell = new SmithLife(0, 0, 8.0);
    board.add_cell(cell);
    EXPECT_EQ(board.get_current_population(), 1);
    CellularAutomaton *cell2 = board.get_cell(0, 0);
    DiscreteAutomaton *cell3 = dynamic_cast<DiscreteAutomaton*>(cell2);
    // state persistence
    EXPECT_EQ(cell3->get_x(), 0);
    EXPECT_EQ(cell3->get_y(), 0);
    EXPECT_EQ(cell3->get_value(), 8.0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}