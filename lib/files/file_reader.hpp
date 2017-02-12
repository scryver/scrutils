#ifndef SCRYVER_FILES_FILE_READER_HPP
#define SCRYVER_FILES_FILE_READER_HPP

#include <cstdint>

#include <string>
#include <vector>
#include <fstream>

namespace Scryver {

namespace Files {

bool readFile(const std::string& path, std::string& output);

bool readBinary(const std::string& path, std::vector<uint8_t>& output);

}  // namespace Files

}  // namespace Scryver

#endif  // SCRYVER_FILES_FILE_READER_HPP
