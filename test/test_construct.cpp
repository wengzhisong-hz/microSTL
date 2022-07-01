#include <gtest/gtest.h>
#include "../memory/construct.h"

using namespace MicroSTL;

class Obj {
public:
    static int val;

    ~Obj();
};

int Obj::val = 1;

Obj::~Obj() {
    val = 2;
}

TEST(construct, construct) {
    Obj obj;
    Obj *address = static_cast<Obj *>(malloc(sizeof obj));
    construct(address, obj);
    ASSERT_EQ(address->val, 1);
}

TEST(construct, trivial_destructor) {
    std::vector<int> vec(10, 1);
    ::destroy(vec.begin(), vec.end());
    ASSERT_EQ(vec[0], 1);
    ASSERT_EQ(vec[9], 1);
}

TEST(construct, non_trivial_destructor) {
    Obj obj;
    std::vector<Obj> vec(10, obj);
    int pre_size = vec.size();
    ::destroy(vec.begin(), vec.end());
    ASSERT_EQ(vec.size(), pre_size);
    ASSERT_EQ(vec[0].val, 2);
    ASSERT_EQ(vec[9].val, 2);
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}