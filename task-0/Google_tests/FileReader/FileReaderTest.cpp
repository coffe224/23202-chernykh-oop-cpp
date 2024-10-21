#include <gtest/gtest.h>

#include "../../src/FileReader/FileReader.h"

TEST(FileReaderTestSuiteInitial, IsClosedInitial) {
    FileReader fileReader;
    ASSERT_EQ(fileReader.isOpen(), false) << "isOpen() returns 'true' initially";
}

TEST(FileReaderTestSuiteInitial, IsEOFInitial) {
    FileReader fileReader;
    ASSERT_EQ(fileReader.isEOF(), true) << "isEOF() returns 'false' initially";
}

TEST(FileReaderTestSuiteInitial, GetlineInitial) {
    FileReader fileReader;
    std::string default_line;
    std::string input_line = default_line;
    fileReader.getLine(input_line);
    ASSERT_EQ(default_line, input_line) << "getLine() changing line initially";
}

TEST(FileReaderTestSuiteInitial, CloseFileInitial) {
    FileReader fileReader;
    fileReader.closeFile();
    ASSERT_EQ(fileReader.isOpen(), false) << "closeFile() changing isOpen() to 'true' initially";
}


TEST(FileReaderTestSuiteFileExistence, IsClosedOnWrongFile) {
    FileReader fileReader;
    fileReader.openFile("NotExistingFile.txt");
    ASSERT_EQ(fileReader.isOpen(), false) << "isOpen() returns 'true' on non existent file";
}

TEST(FileReaderTestSuiteFileExistence, IsOpenOnOpenedFile) {
    FileReader fileReader;
    fileReader.openFile("ExistingFile.txt");
    ASSERT_EQ(fileReader.isOpen(), true) << "isOpen() returns 'false' on opened file";
}

TEST(FileReaderTestSuiteFileExistence, IsClosedOnClosedFile) {
    FileReader fileReader;
    fileReader.openFile("ExistingFile.txt");
    fileReader.closeFile();
    ASSERT_EQ(fileReader.isOpen(), false) << "isOpen() returns 'true' on closed file";
}


TEST(FileReaderTestSuiteEmptyFile, IsEOFOnEmptyFile) {
    FileReader fileReader;
    fileReader.openFile("EmptyFile.txt");
    if (fileReader.isOpen()) {
        ASSERT_EQ(fileReader.isEOF(), true) << "isEOF() returns 'false' on empty file";
    } else {
        ASSERT_EQ(1, 0) << "Can't open EmptyFile.txt";
    }
}

TEST(FileReaderTestSuiteEmptyFile, GetlineOnEmptyFile) {
    FileReader fileReader;
    fileReader.openFile("EmptyFile.txt");

    std::string default_line;
    std::string input_line = default_line;
    if (fileReader.isOpen()) {
        fileReader.getLine(input_line);
        ASSERT_EQ(default_line, input_line) << "getLine() changing line on empty file";
    } else {
        ASSERT_EQ(1, 0) << "Can't open EmptyFile.txt";
    }
}

TEST(FileReaderTestSuiteNormalFile, IsEOFOnNonEmptyFile) {
    FileReader fileReader;
    fileReader.openFile("FileExample.txt");
    if (fileReader.isOpen()) {
        ASSERT_EQ(fileReader.isEOF(), false) << "isEOF() returns 'true' on non empty file";
    } else {
        ASSERT_EQ(1, 0) << "Can't open FileExample.txt";
    }
}

TEST(FileReaderTestSuiteNormalFile, GetlineOnFile) {
    FileReader fileReader;
    fileReader.openFile("FileExample.txt");

    std::string message = "message example";
    std::string input_line;
    if (fileReader.isOpen()) {
        fileReader.getLine(input_line);
        ASSERT_EQ(input_line, message) << "getLine() gets wrong message";
    } else {
        ASSERT_EQ(1, 0) << "Can't open FileExample.txt";
    }
}

TEST(FileReaderTestSuiteNormalFile, FullCycle) {
    FileReader fileReader;
    fileReader.openFile("FileExample1.txt");

    std::string message1 = "message example 1";
    std::string message2 = "message example 2";

    std::string input_line;
    if (fileReader.isOpen()) {
        fileReader.getLine(input_line);
        ASSERT_EQ(input_line, message1);
        ASSERT_EQ(fileReader.isEOF(), false);

        input_line.clear();

        fileReader.getLine(input_line);
        ASSERT_EQ(input_line, message2);
        ASSERT_EQ(fileReader.isEOF(), true);

        fileReader.closeFile();
        ASSERT_EQ(fileReader.isOpen(), false);
    } else {
        ASSERT_EQ(1, 0) << "Can't open FileExample1.txt";
    }
}
