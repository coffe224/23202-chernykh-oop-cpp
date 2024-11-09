cmake_minimum_required(VERSION 3.6)
project(task-1-project LANGUAGES CXX)

add_library(BitArray src/BitArray.h src/BitArray.cpp)
add_subdirectory(test)