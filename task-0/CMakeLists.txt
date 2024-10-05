cmake_minimum_required(VERSION 3.6)
project(task-0-project)

add_executable(test src/main.cpp src/FileReader.cpp include/FileReader.h src/Parser.cpp include/Parser.h src/Statistics.cpp include/Statistics.h include/FileWriter.h src/FileWriter.cpp)
