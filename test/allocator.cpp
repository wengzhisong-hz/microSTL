#include <gtest/gtest.h>
#include <numeric>
#include <vector>
#include <iostream>
#include "../allocator/allocator.h"

using namespace std;

TEST(Test, test) {
    int iArray[5] = {0, 1, 2, 3, 4};
    vector<int, MicroSTL::allocator<int>> vec(iArray, iArray + 5);
    for (int i = 0; i < vec.size(); i++) {
        EXPECT_EQ(i, vec[i]);
    }
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}