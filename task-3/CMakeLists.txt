cmake_minimum_required(VERSION 3.11)

project(task-3-project LANGUAGES CXX)

add_library(BasicFileReader src/FileReaders/BasicFileReader.h src/FileReaders/BasicFileReader.cpp)
add_library(FileReader src/FileReaders/FileReader.h src/FileReaders/FileReader.cpp)
add_library(ByteReader src/FileReaders/ByteReader.h src/FileReaders/ByteReader.cpp)

target_link_libraries(FileReader BasicFileReader)
target_link_libraries(ByteReader BasicFileReader)



add_library(ArgParser src/ArgParser.h src/ArgParser.cpp)
add_library(WavReader src/WavReader.h src/WavReader.cpp)

add_executable(test src/main.cpp)

target_link_libraries(WavReader FileReader)
target_link_libraries(test ArgParser WavReader)
