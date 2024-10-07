//
// Created by velocitatem on 10/4/24.
//


#include <gtest/gtest.h>

/// tes t1 + 1
///

TEST(test1, test1) {
    EXPECT_EQ(1, 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}