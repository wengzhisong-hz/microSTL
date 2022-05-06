cmake_minimum_required(VERSION 2.8)

project(microSTL)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -Wall")

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})


add_executable(Tests
        test/allocator.cpp
        allocator/allocator.cpp
        allocator/allocator.h)

target_link_libraries(Tests ${GTEST_BOTH_LIBRARIES})
target_link_libraries(Tests ${CMAKE_THREAD_LIBS_INIT})

add_test(Test Tests)
enable_testing()