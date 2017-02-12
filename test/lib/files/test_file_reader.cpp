#include <gtest/gtest.h>

#include <string>

#include <Scryver/Files/FileReader>

const std::string testFile = "build/test/file_reader.txt";

using namespace Scryver::Files;


TEST(FileReader, CanOpenFile)
{
    std::string output;
    ASSERT_TRUE(readFile(testFile, output));
}
