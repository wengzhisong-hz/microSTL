#include <gtest/gtest.h>
#include <string>
#include "../iterator/iterator_traits.h"
#include "../iterator/iterator.h"

using namespace MicroSTL;

template<typename T>
std::string get_parent_type(input_iterator_tag, T) {
    return "input_iterator_tag";
}

template<typename T>
std::string get_parent_type(output_iterator_tag, T) {
    return "output_iterator_tag";
}

template<typename T>
std::string get_type(T) {
    return "都不匹配";
}

template<>
std::string get_type(output_iterator_tag) {
    return "output_iterator_tag";
}

template<>
std::string get_type(input_iterator_tag) {
    return "input_iterator_tag";
}

template<>
std::string get_type(int) {
    return "int";
}

template<>
std::string get_type(bool) {
    return "bool";
}

template<>
std::string get_type(char *) {
    return "char *";
}

template<>
std::string get_type(const long *) {
    return "const long *";
}

template<>
std::string get_type(ptrdiff_t) {
    return "ptrdiff_t";
}

iterator<output_iterator_tag, int> iter1;
iterator<forward_iterator_tag, char *> iter2;
iterator<input_iterator_tag, const long *> iter3;
iterator<output_iterator_tag, int> &iter11 = iter1;


TEST(iterator_traits, iterator_category) {
    EXPECT_EQ(get_type(iterator_category(iter1)), "output_iterator_tag");
    // 此处因为forward_iterator_tag继承了input_iterator_tag
    // 即使get_parent_type没有匹配forward_iterator_tag类型的重载
    // 仍然会寻找它的继承关系，匹配到input_iterator_tag
    EXPECT_EQ(get_parent_type(iterator_category(iter2), nullptr), "input_iterator_tag");
}

TEST(iterator_traits, value_type) {
    EXPECT_EQ(get_type(value_type(iter11)), "int");
    EXPECT_EQ(get_type(value_type(iter2)), "char *");
    EXPECT_EQ(get_type(value_type(iter3)), "const long *");
}

TEST(iterator_traits, distance_type) {
    EXPECT_EQ(get_type(distance_type(iter1)), "ptrdiff_t");
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}