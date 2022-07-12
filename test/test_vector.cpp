#include <gtest/gtest.h>
#include "../container/vector.h"

using namespace MicroSTL;

TEST(vector, base) {
    vector<char> vec(10, 'A');
    EXPECT_EQ(*vec.begin(), 'A');
    EXPECT_EQ(*(vec.end() - 1), 'A');
    EXPECT_EQ(vec.front(), 'A');
    EXPECT_EQ(vec.back(), 'A');
    EXPECT_NE(*vec.end(), 'A');
    // 初始容量 = begin - end
    EXPECT_EQ(vec.capacity(), 10);
    EXPECT_EQ(vec.empty(), false);
    EXPECT_EQ(vec[9], 'A');
}

TEST(vector, pop_back) {
    vector<int> vec(2, 1);
    vec.pop_back();
    EXPECT_EQ(vec.size(), 1);
    vec.pop_back();
    EXPECT_EQ(vec.size(), 0);
}

TEST(vector, push_back) {
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
    EXPECT_EQ(vec[3], 4);
    EXPECT_EQ(vec[4], 5);
}

TEST(vector, erase) {
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.erase(vec.begin() + 1);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 3);

    vec.clear();
    EXPECT_EQ(vec.size(), 0);
}

TEST(vector, resize) {
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);

    vec.resize(1);
    EXPECT_EQ(vec.size(), 1);
    EXPECT_EQ(vec[0], 1);


    vec.resize(5);
    EXPECT_EQ(vec.size(), 5);
    EXPECT_EQ(vec[4], 0);

    vec.resize(10, 10);
    EXPECT_EQ(vec[9], 10);
}


TEST(vector, insert) {
    vector<int> vec;
    for (int i = 0; i <= 1000; i++) {
        vec.push_back(i);
        std::cout << vec[i] << ", ";
    }
    for (int i = 0; i <= 1000; i++) {
        if (vec[i] != i) {
            std::cout << i << ", ";
        }
    }


    // 空间充足 elements_after > size


    // 空间充足 elements_after < size

    // 空间不足

}


int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

