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
            auto cell = std::make_unique<BasicLife>(i, j, 1.0);
            board.add_cell(std::move(cell));
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
    auto cell = std::make_unique<SmithLife>(0, 0, 1);
    board.add_cell(std::move(cell));
    EXPECT_EQ(board.get_current_population(), 1);
    CellularAutomaton *cell2 = board.get_cell(0, 0);
    DiscreteAutomaton *cell3 = dynamic_cast<DiscreteAutomaton*>(cell2);
    // state persistence
    EXPECT_EQ(cell3->get_x(), 0);
    EXPECT_EQ(cell3->get_y(), 0);
    EXPECT_EQ(cell3->get_value(), 1);
}

TEST(BoardTest, AddCell2) {
    Board board(5, 5, GRID, 3);
    auto cell = std::make_unique<SmithLife>(0, 0, 8.0);
    board.add_cell(std::move(cell));
    auto cell2 = std::make_unique<SmithLife>(0, 1, 8.0);
    board.add_cell(std::move(cell2));
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

// test value assignment
TEST(DiscreteAutomatonTest, Value) {
    SmithLife cell(0, 0, 1.0);
    EXPECT_EQ(cell.get_value(), 1.0);
    cell.set_value(2.0);
    EXPECT_EQ(cell.get_value(), 2.0);
}

TEST(SmithLifeTest, Compute) { // testing with a single cell that will die
    Board board(2, 2, GRID, 2);
    auto cell = std::make_unique<SmithLife>(0, 0, 1.0);
    board.add_cell(std::move(cell));
    SmithLife::compute(board);
    DiscreteAutomaton *cell2 = dynamic_cast<DiscreteAutomaton*>(board.get_cell(0, 0));
    EXPECT_EQ(cell2->get_value(), 0.0);
    board.add_cell(std::make_unique<SmithLife>(0, 1, 1.0));
    board.add_cell(std::make_unique<SmithLife>(1, 1, 1.0));
    board.add_cell(std::make_unique<SmithLife>(1, 0, 1.0));
    /// we give new neighbors to the cell and it comes back to life
    SmithLife::compute(board);
    DiscreteAutomaton *cell3 = dynamic_cast<DiscreteAutomaton*>(board.get_cell(0, 0));
    EXPECT_EQ(cell3->get_value(), 1.0);
}

TEST(BoardInitializerTest, Initializer) {
    Board board(5, 5, GRID, 3);
    EXPECT_EQ(board.get_width(), 5);
    EXPECT_EQ(board.get_height(), 5);
    EXPECT_EQ(board.get_current_population(), 0);
}

TEST(BoardCopyConstructorTest, CopyConstructor) {
    Board board(5, 5, GRID, 3);
    auto cell = std::make_unique<SmithLife>(0, 0, 1.0);
    board.add_cell(std::move(cell));
    Board board1 = board;
    EXPECT_EQ(board1.get_current_population(), 1);
    DiscreteAutomaton *cell2 = dynamic_cast<DiscreteAutomaton*>(board1.get_cell(0, 0));
    EXPECT_EQ(cell2->get_value(), 1.0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}