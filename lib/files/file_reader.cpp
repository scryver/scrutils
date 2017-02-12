#include "file_reader.hpp"

#include <string>
#include <fstream>

bool Scryver::Files::readFile(const std::string& path, std::string& output)
{
    std::ifstream fileStream(path, std::ios::in);
    if (fileStream.is_open())
    {
        std::string line = "";
        while (getline(fileStream, line))
            output += line + "\n";
        fileStream.close();
        return true;
    }

    return false;
}
