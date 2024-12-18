cmake_minimum_required(VERSION 3.11)
project(task-4-project LANGUAGES CXX)

add_executable(task-4 src/main.cpp src/TuplePrinter.h src/CSVParser.h src/StreamParser/StreamParser.h src/StreamParser/StreamParser.cpp)
