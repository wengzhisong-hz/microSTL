find_package(GTest REQUIRED)

add_executable(test_alloc test_alloc.cpp)
add_executable(test_construct test_construct.cpp)
add_executable(test_uninitialized test_uninitialized.cpp)

add_executable(test_type_traits test_type_traits.cpp)
add_executable(test_iterator test_iterator.cpp)


target_link_libraries(test_alloc ${GTEST_BOTH_LIBRARIES})
target_link_libraries(test_construct ${GTEST_BOTH_LIBRARIES})
target_link_libraries(test_uninitialized ${GTEST_BOTH_LIBRARIES})

target_link_libraries(test_type_traits ${GTEST_BOTH_LIBRARIES})
target_link_libraries(test_iterator ${GTEST_BOTH_LIBRARIES})


add_test(测试alloc test_alloc)
add_test(测试construct test_construct)
add_test(测试uninitialized test_uninitialized)

add_test(测试type_traits test_type_traits)
add_test(测试iterator test_iterator)
