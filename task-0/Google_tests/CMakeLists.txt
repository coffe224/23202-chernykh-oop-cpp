project(Google_tests)
add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(SOURCES 
    FileReader/FileReaderTest.cpp 
    FileWriter/FileWriterTest.cpp 
    Parser/ParserTest.cpp 
    Statistics/StatisticsTest.cpp
    Converter/ConverterTest.cpp)

add_executable(Google_Tests_run ${SOURCES})

target_link_libraries(Google_Tests_run FileReader FileWriter Parser Statistics Converter)
target_link_libraries(Google_Tests_run gtest gtest_main)