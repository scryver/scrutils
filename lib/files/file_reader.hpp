#ifndef SCRYVER_FILES_FILE_READER_HPP
#define SCRYVER_FILES_FILE_READER_HPP

#include <string>

namespace Scryver {

namespace Files {

bool readFile(const std::string& path, std::string& output);

}  // namespace Files

}  // namespace Scryver

#endif  // SCRYVER_FILES_FILE_READER_HPP
