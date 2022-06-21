#include <gtest/gtest.h>
#include "../src/allocator.h"


using namespace std;

TEST(示例, 测试相等) {
    EXPECT_EQ(1, MicroSTL::allocator::add(1));
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}