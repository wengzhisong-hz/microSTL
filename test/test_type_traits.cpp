#include <gtest/gtest.h>
#include "../iterator/type_traits.h"

using namespace MicroSTL;

// 未定义的类型
template<typename T>
int get_type(T type) {
    return 0;
}

// 全特化 true_type
template<>
int get_type<true_type>(true_type type) {
    return 1;
}

// 全特化 false_type
template<>
int get_type<false_type>(false_type type) {
    return 2;
}


TEST(测试type_traits, 测试POD类型) {
    using t1 = typename type_traits<int>::is_POD_type;
    using t2 = typename type_traits<char>::is_POD_type;
    using t3 = typename type_traits<int *>::is_POD_type;
    using t4 = typename type_traits<const int *>::is_POD_type;

    struct other {
        int a;
        char b;
    };

    t1 o1;
    t2 o2;
    t3 o3;
    t4 o4;

    other o5;

    EXPECT_EQ(1, get_type(o1));
    EXPECT_EQ(1, get_type(o2));
    EXPECT_EQ(1, get_type(o3));
    EXPECT_EQ(1, get_type(o4));
    EXPECT_EQ(0, get_type(o5));
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
