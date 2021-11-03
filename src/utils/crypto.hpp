#pragma once

#include <iostream>

namespace utils {

namespace crypto {

void sha256_string(std::string string, std::string &output);
bool sha256_file(std::string path, std::string &output);

}  // namespace crypto

}  // namespace utils