#include "file_reader.hpp"

#include <string>
#include <fstream>

bool Scryver::Files::readFile(const std::string& path,
                              std::string& output)
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

bool Scryver::Files::readBinary(const std::string& path,
                                std::vector<uint8_t>& output)
{
    if (FILE *fp = fopen(path.c_str(), "rb"))
    {
        uint8_t buffer[100];
        while (size_t len = fread(buffer, 1, sizeof(buffer), fp))
            output.insert(output.end(), buffer, buffer + len);
        fclose(fp);

        return true;
    }
    return false;
}
