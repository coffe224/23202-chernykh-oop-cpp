cmake_minimum_required(VERSION 3.11)
project(task-1-project LANGUAGES CXX)


add_library(Universe src/Universe/Universe.h src/Universe/Universe.cpp src/Universe/UniverseWrapper.h src/Universe/UniverseWrapper.cpp)

add_library(FileReader src/UniverseParser/FileReader.h src/UniverseParser/FileReader.cpp)
add_library(UniverseParser src/UniverseParser/UniverseParser.h src/UniverseParser/UniverseParser.cpp)

target_link_libraries(UniverseParser FileReader Universe)

add_library(FileWriter src/OutputHandler/FileWriter.h src/OutputHandler/FileWriter.cpp)
add_library(Printer src/OutputHandler/Printer.h src/OutputHandler/Printer.cpp)
add_library(OutputHandler src/OutputHandler/OutputHandler.h src/OutputHandler/OutputHandler.cpp)

target_link_libraries(OutputHandler Printer FileWriter)


add_library(InputListener src/Controller/CommandListener/InputListener.h src/Controller/CommandListener/InputListener.cpp)
add_library(StringParser src/Controller/CommandListener/StringParser.h src/Controller/CommandListener/StringParser.cpp)
add_library(CommandListener src/Controller/CommandListener/CommandListener.h src/Controller/CommandListener/CommandListener.cpp)


target_link_libraries(InputListener StringParser)
target_link_libraries(CommandListener InputListener)

add_library(Controller src/Controller/Controller.h src/Controller/Controller.cpp)
target_link_libraries(Controller UniverseParser OutputHandler CommandListener)

add_library(ArgParser src/ArgParser/ArgParser.h src/ArgParser/ArgParser.cpp)

add_executable(test src/main.cpp)
target_link_libraries(test Controller ArgParser)
