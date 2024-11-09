project(test)
add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Google_Tests_run BitArrayTest.cpp)

target_link_libraries(Google_Tests_run BitArray)
target_link_libraries(Google_Tests_run gtest gtest_main)