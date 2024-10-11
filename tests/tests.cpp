//
// Created by velocitatem on 10/4/24.
//


#include <gtest/gtest.h>
#include <board.h>
#include <cells.h>

TEST(test1, test1) {
    // A test to test tests
    EXPECT_EQ(1, 1);
}

// basic life test
TEST(BasicLifeTest, Initialization) {
    Board board(5, 5, GRID, 3);
    for (int i = 0; i < 5; i += 1) {
        for (int j = 0; j < 5; j += 1) {
            BasicLife *cell = new BasicLife(i, j, 1.0);
            board.add_cell(cell);
        }
    }

    for (int i = 0; i < 5; i += 1) {
        for (int j = 0; j < 5; j += 1) {
            BasicLife *cell = dynamic_cast<BasicLife*>(board.get_cell(i, j));
            EXPECT_EQ(cell->get_x(), i);
            EXPECT_EQ(cell->get_y(), j);
            EXPECT_EQ(cell->get_value(), 1.0);
        }
    }

    BasicLife::compute(&board);

    for (int i = 0; i < 5; i += 1) {
        for (int j = 0; j < 5; j += 1) {
            BasicLife *cell = dynamic_cast<BasicLife*>(board.get_cell(i, j));
            EXPECT_EQ(cell->get_x(), i);
            EXPECT_EQ(cell->get_y(), j);
            EXPECT_EQ(cell->get_value(), 2.0);
        }
    }
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

TEST(BoardTest, AddCell2) {
    Board board(5, 5, GRID, 3);
    SmithLife *cell = new SmithLife(0, 0, 8.0);
    board.add_cell(cell);
    SmithLife *cell2 = new SmithLife(0, 0, 8.0);
    board.add_cell(cell2);
    EXPECT_EQ(board.get_current_population(), 2);
    CellularAutomaton *cell3 = board.get_cell(0, 0);
    DiscreteAutomaton *cell4 = dynamic_cast<DiscreteAutomaton*>(cell3);
    // state persistence
    EXPECT_EQ(cell4->get_x(), 0);
    EXPECT_EQ(cell4->get_y(), 0);
    EXPECT_EQ(cell4->get_value(), 8.0);
}

// compare 2 cells
TEST(DiscreteAutomatonTest, Compare) {
    SmithLife cell(0, 0, 1.0);
    SmithLife cell2(0, 0, 1.0);
    EXPECT_EQ(cell, cell2);
}


TEST(BoardConstructorTest, Constructor) {
    Board b;
    EXPECT_EQ(b.get_current_population(), 0);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}