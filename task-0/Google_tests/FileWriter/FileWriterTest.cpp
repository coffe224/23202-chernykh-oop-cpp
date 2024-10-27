#include <gtest/gtest.h>
#include <cstdio>

#include "../../src/FileWriter/FileWriter.h"

// Initial
TEST(FileWriterTestSuiteInitial, IsOpenInitial) {
    FileWriter fileWriter;
    ASSERT_EQ(fileWriter.isOpen(), false);
}

TEST(FileWriterTestSuiteInitial, CloseInitial) {
    FileWriter fileWriter;
    fileWriter.closeFile();
    ASSERT_EQ(fileWriter.isOpen(), false);
}

TEST(FileWriterTestSuiteInitial, WriteLineInitial) {
    FileWriter fileWriter;
    fileWriter.writeLine("test");
    ASSERT_EQ(fileWriter.isOpen(), false);
}

//Wrong Name
TEST(FileWriterTestSuiteWrongName, OpenWrongFilename) {
    FileWriter fileWriter;
    fileWriter.openFile("");
    ASSERT_EQ(fileWriter.isOpen(), false);
}

// Normal
TEST(FileWriterTestSuiteNormal, OpenFile) {
    FileWriter fileWriter;
    fileWriter.openFile("WriteExample.csv");
    ASSERT_EQ(fileWriter.isOpen(), true);
    fileWriter.closeFile();
    ASSERT_EQ(fileWriter.isOpen(), false);
    ASSERT_EQ(std::remove("WriteExample.csv"), 0);
}

TEST(FileWriterTestSuiteNormal, WriteToAFile) {
    FileWriter fileWriter;
    fileWriter.openFile("WriteExample.csv");
    if (fileWriter.isOpen()) {
        std::string message1 = "message 1";
        std::string message2 = "message 2";
        fileWriter.writeLine(message1);
        fileWriter.writeLine(message2);
        fileWriter.closeFile();

        std::ifstream check("WriteExample.csv");
        ASSERT_EQ(!check, false);

        std::string check_message1;
        std::getline(check, check_message1);
        ASSERT_EQ(message1, check_message1);

        std::string check_message2;
        std::getline(check, check_message2);
        ASSERT_EQ(message2, check_message2);

        check.close();

        ASSERT_EQ(std::remove("WriteExample.csv"), 0);
    } else {
        ASSERT_EQ(1, 0) << "Can't open WriteExample.csv";
    }
}
