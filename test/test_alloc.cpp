#include <gtest/gtest.h>
#include <string>
#include "../memory/alloc.h"

using namespace MicroSTL;

TEST(AllocByMalloc, allocate) {
    size_t size = 100;
    void *ptr = AllocByMalloc::allocate(size);
    EXPECT_TRUE(ptr);
}

TEST(AllocByMalloc, reallocate) {
    size_t size = 10;
    void *old_ptr = AllocByMalloc::allocate(size);
    void *new_ptr = AllocByMalloc::reallocate(old_ptr, 10, 20);
    EXPECT_TRUE(new_ptr);
}

TEST(AllocByMalloc, deallocate) {
    size_t size = 10;
    char *ptr = static_cast<char *>(AllocByMalloc::allocate(size));
    strcpy(ptr, "12345");
    char first = *ptr;
    EXPECT_EQ(first, '1');
    AllocByMalloc::deallocate(ptr, size);
    char _first = *ptr;
    EXPECT_NE(_first, '1');
}

int temp = 0;

void do_nothing() {
    temp++;
};

TEST(AllocByMalloc, set_oom_user_handler) {
    void (*oom_fn)();
    void (*old_fn)();
    oom_fn = do_nothing;
    old_fn = AllocByMalloc::set_oom_user_handler(oom_fn);
    old_fn = AllocByMalloc::set_oom_user_handler(oom_fn);
    oom_fn();
    EXPECT_EQ(temp, 1);
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}