cmake_minimum_required(VERSION 3.11)
project(task-1-project LANGUAGES CXX)

add_library(ArgParser src/ArgParser.h src/ArgParser.cpp)
add_library(CommandListener src/CommandListener.h src/CommandListener.cpp)
add_library(Controller src/Controller.h src/Controller.cpp)
add_library(FileReader src/FileReader.h src/FileReader.cpp)
add_library(FileWriter src/FileWriter.h src/FileWriter.cpp)
add_library(InputListener src/InputListener.h src/InputListener.cpp)
add_library(Model src/Model.h src/Model.cpp)
add_library(Printer src/Printer.h src/Printer.cpp)
add_library(StringParser src/StringParser.h src/StringParser.cpp)
add_library(Universe src/Universe.h src/Universe.cpp)
add_library(View src/View.h src/View.cpp)

add_executable(test src/main.cpp)

target_link_libraries(Model Universe)
target_link_libraries(View FileWriter Printer Model)

target_link_libraries(InputListener StringParser)
target_link_libraries(CommandListener InputListener)
target_link_libraries(Controller Model View FileReader CommandListener StringParser)

target_link_libraries(test Controller ArgParser)