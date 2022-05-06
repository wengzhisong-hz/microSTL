#include <gtest/gtest.h>
#include <numeric>
#include "../allocator/allocator.h"

TEST(Test, test) {
    MicroSTL::Allocator allocator;
    EXPECT_EQ(allocator.add(1, 2), 3);
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}