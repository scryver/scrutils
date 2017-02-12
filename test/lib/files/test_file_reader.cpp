#include <gtest/gtest.h>

#include <cstdint>
#include <string>
#include <iostream>

#include "Scryver/Files/FileReader.hpp"

const std::string testFile = "build/test/file_reader.txt";
const std::string testBinary = "build/test/binary_file.txt";

using std::cout;
using std::endl;

using namespace Scryver::Files;


TEST(FileReader, CanOpenFile)
{
    std::string output;
    ASSERT_TRUE(readFile(testFile, output));
}

TEST(FileReader, ReturnsNewlines)
{
    std::string output;
    readFile(testFile, output);

    ASSERT_EQ("This is a file!\nWith a new line.\nAnd some more info?\n", output);
}

TEST(FileReader, CanOpenBinary)
{
    std::vector<uint8_t> output;
    ASSERT_TRUE(readBinary(testBinary, output));
}

TEST(FileReader, ReturnsVector)
{
    std::vector<uint8_t> output;
    readBinary(testBinary, output);

    ASSERT_EQ(4u, output.size());
    for (size_t i = 0; i < output.size(); i++)
    {
        ASSERT_EQ(i + 1, output[i]);
    }
}

TEST(FileReader, ReturnFalseIfNotFound)
{
    std::string outStr;
    ASSERT_FALSE(readFile("somefile/somewhere/or/not.txt", outStr));

    std::vector<uint8_t> outVec;
    ASSERT_FALSE(readBinary("somefile/somewhere/or/not.txt", outVec));
}
