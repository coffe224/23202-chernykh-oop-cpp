cmake_minimum_required(VERSION 3.11)

project(task-3-project LANGUAGES CXX)

add_library(BasicFileReader src/FileReaders/BasicFileReader.h src/FileReaders/BasicFileReader.cpp)
add_library(ByteReader src/FileReaders/ByteReader.h src/FileReaders/ByteReader.cpp)
add_library(FileReader src/FileReaders/FileReader.h src/FileReaders/FileReader.cpp)

target_link_libraries(FileReader BasicFileReader)
target_link_libraries(ByteReader BasicFileReader)

add_library(Sample src/Sample.h src/Sample.cpp)
add_library(WavFile src/WavFile.h src/WavFile.cpp)
target_link_libraries(WavFile Sample)

add_library(WavReader src/WavReader.h src/WavReader.cpp)
target_link_libraries(WavReader ByteReader WavFile)

add_library(Converter src/Converter.h src/Converter.cpp)
add_library(ConverterWrapper src/ConverterWrapper.h src/ConverterWrapper.cpp)
target_link_libraries(Converter Sample)
target_link_libraries(ConverterWrapper Converter)

add_library(StringParser src/StringParser.h src/StringParser.cpp)
add_library(ConfigFileParser src/ConfigFileParser.h src/ConfigFileParser.cpp)
target_link_libraries(ConfigFileParser FileReader StringParser ConverterWrapper)

add_library(Controller src/Controller.h src/Controller.cpp)
target_link_libraries(Controller ConfigFileParser WavReader)


add_library(ArgParser src/ArgParser.h src/ArgParser.cpp)
add_executable(test src/main.cpp)

target_link_libraries(test ArgParser Controller)
