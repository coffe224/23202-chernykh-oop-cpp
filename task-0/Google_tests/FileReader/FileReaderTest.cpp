#include <gtest/gtest.h>
#include <cstdio>

#include "../../src/FileReader/FileReader.h"

TEST(FileReaderTestSuiteInitial, IsClosedInitial) {
    FileReader fileReader;
    ASSERT_EQ(fileReader.isOpen(), false);
}

TEST(FileReaderTestSuiteInitial, IsEOFInitial) {
    FileReader fileReader;
    ASSERT_EQ(fileReader.isEOF(), true);
}

TEST(FileReaderTestSuiteInitial, GetlineInitial) {
    FileReader fileReader;
    std::string default_line;
    std::string input_line = default_line;
    fileReader.getLine(input_line);
    ASSERT_EQ(default_line, input_line);
}

TEST(FileReaderTestSuiteInitial, CloseFileInitial) {
    FileReader fileReader;
    fileReader.closeFile();
    ASSERT_EQ(fileReader.isOpen(), false);
}


TEST(FileReaderTestSuiteFileExistence, IsClosedOnWrongFile) {
    FileReader fileReader;
    fileReader.openFile("NotExistingFile.txt");
    ASSERT_EQ(fileReader.isOpen(), false);
}

TEST(FileReaderTestSuiteFileExistence, IsOpenOnOpenedFile) {
    std::ofstream file_creator("ExistingFile.txt");
    file_creator.close();

    FileReader fileReader;
    fileReader.openFile("ExistingFile.txt");
    ASSERT_EQ(fileReader.isOpen(), true);

    ASSERT_EQ(std::remove("ExistingFile.txt"), 0);
}

TEST(FileReaderTestSuiteFileExistence, IsClosedOnClosedFile) {
    std::ofstream file_creator("ExistingFile.txt");
    file_creator.close();

    FileReader fileReader;
    fileReader.openFile("ExistingFile.txt");
    fileReader.closeFile();
    ASSERT_EQ(fileReader.isOpen(), false);

    ASSERT_EQ(std::remove("ExistingFile.txt"), 0);
}


TEST(FileReaderTestSuiteEmptyFile, IsEOFOnEmptyFile) {
    std::ofstream file_creator("EmptyFile.txt");
    file_creator.close();

    FileReader fileReader;
    fileReader.openFile("EmptyFile.txt");
    if (fileReader.isOpen()) {
        ASSERT_EQ(fileReader.isEOF(), true);
        fileReader.closeFile();
        ASSERT_EQ(std::remove("EmptyFile.txt"), 0);
    } else {
        ASSERT_EQ(1, 0) << "Can't open EmptyFile.txt";
    }
}

TEST(FileReaderTestSuiteEmptyFile, GetlineOnEmptyFile) {
    std::ofstream file_creator("EmptyFile.txt");
    file_creator.close();

    FileReader fileReader;
    fileReader.openFile("EmptyFile.txt");

    std::string default_line = "something before input";
    std::string input_line = default_line;
    if (fileReader.isOpen()) {
        fileReader.getLine(input_line);
        ASSERT_EQ(default_line, input_line);

        fileReader.closeFile();
        ASSERT_EQ(std::remove("EmptyFile.txt"), 0);
    } else {
        ASSERT_EQ(1, 0) << "Can't open EmptyFile.txt";
    }
}

TEST(FileReaderTestSuiteNormalFile, IsEOFOnNonEmptyFile) {
    std::ofstream file_creator("FileExample.txt");
    file_creator << "something";
    file_creator.close();

    FileReader fileReader;
    fileReader.openFile("FileExample.txt");
    if (fileReader.isOpen()) {
        ASSERT_EQ(fileReader.isEOF(), false);
        
        fileReader.closeFile();
        ASSERT_EQ(std::remove("FileExample.txt"), 0);
    } else {
        ASSERT_EQ(1, 0) << "Can't open FileExample.txt";
    }
}

TEST(FileReaderTestSuiteNormalFile, GetlineOnFile) {
    std::string message = "something";
    
    std::ofstream file_creator("FileExample.txt");
    file_creator << message;
    file_creator.close();

    FileReader fileReader;
    fileReader.openFile("FileExample.txt");

    std::string input_line;
    if (fileReader.isOpen()) {
        fileReader.getLine(input_line);
        ASSERT_EQ(input_line, message);

        fileReader.closeFile();
        ASSERT_EQ(std::remove("FileExample.txt"), 0);
    } else {
        ASSERT_EQ(1, 0) << "Can't open FileExample.txt";
    }
}

TEST(FileReaderTestSuiteNormalFile, FullCycle) {
    std::string message1 = "message example 1";
    std::string message2 = "message example 2";

    std::ofstream file_creator("FileExample.txt");
    file_creator << message1 << '\n';
    file_creator << message2;
    file_creator.close();

    FileReader fileReader;
    fileReader.openFile("FileExample.txt");

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

        ASSERT_EQ(std::remove("FileExample.txt"), 0);
    } else {
        ASSERT_EQ(1, 0) << "Can't open FileExample.txt";
    }
}
