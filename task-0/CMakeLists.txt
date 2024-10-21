cmake_minimum_required(VERSION 3.6)
project(task-0-project LANGUAGES CXX)

add_subdirectory(src/Controller)
add_subdirectory(src/FileReader)
add_subdirectory(src/FileWriter)
add_subdirectory(src/Converter)
add_subdirectory(src/Parser)
add_subdirectory(src/Statistics)

add_subdirectory(Google_tests)

add_executable(task-0 src/main.cpp)
target_link_libraries(task-0 Controller)

