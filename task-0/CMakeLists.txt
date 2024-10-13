cmake_minimum_required(VERSION 3.6)
project(task-0-project)

set(HEADERS
    src/FileReader/FileReader.h
    src/FileWriter/FileWriter.h
    src/Parser/Parser.h
    src/Statistics/Statistics.h
    # src/Controller/Controller.h
)

set(SOURCES
    src/FileReader/FileReader.cpp
    src/FileWriter/FileWriter.cpp
    src/Parser/Parser.cpp
    src/Statistics/Statistics.cpp
    # src/Controller/Controller.cpp
)

add_executable(test src/main.cpp ${SOURCES} ${HEADERS})