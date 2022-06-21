find_package(GTest REQUIRED)

add_executable(test_allocator test_allocator.cpp)
add_executable(test_type_traits test_type_traits.cpp)


target_link_libraries(test_allocator ${GTEST_BOTH_LIBRARIES})
target_link_libraries(test_type_traits ${GTEST_BOTH_LIBRARIES})

add_test(测试allocator test_allocator)
add_test(测试type_traits test_type_traits)
