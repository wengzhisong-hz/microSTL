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
    vector<int> vec1;
    for (int i = 0; i < 1000; i++) {
        vec1.push_back(i);
        EXPECT_EQ(vec1[i], i);
    }

    struct obj {
        int a = 1;
        bool b = false;
        long c = 100;
    };

    vector<obj> vec2;
    for (int i = 0; i < 1000; i++) {
        obj temp_obj;
        temp_obj.a = i;
        vec2.push_back(temp_obj);
        EXPECT_EQ(vec2[i].a, i);
    }
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
    for (int i = 0; i <= 10; i++) {
        vec.push_back(i);
    }
    vec.insert(vec.begin() + 5, 1, 999);
    EXPECT_EQ(*(vec.begin() + 5), 999);
}


int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

