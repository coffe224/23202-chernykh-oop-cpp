cmake_minimum_required(VERSION 3.6)
project(task-0-project LANGUAGES CXX)

add_library(Controller src/Controller/Controller.cpp src/Controller/Controller.h)
add_library(FileReader src/FileReader/FileReader.cpp src/FileReader/FileReader.h)
add_library(FileWriter src/FileWriter/FileWriter.cpp src/FileWriter/FileWriter.h)
add_library(Converter src/Converter/Converter.cpp src/Converter/Converter.h)
add_library(Parser src/Parser/Parser.cpp src/Parser/Parser.h)
add_library(Statistics src/Statistics/Statistics.cpp src/Statistics/Statistics.h)

add_subdirectory(Google_tests)

add_executable(task-0 src/main.cpp)

target_link_libraries(Controller Converter FileReader FileWriter Parser Statistics)
target_link_libraries(task-0 Controller)
