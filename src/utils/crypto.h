#pragma once

#include <iostream>

namespace utils {

namespace crypto {

void sha256_string(std::string string, std::string &outputBuffer);
int sha256_file(std::string path, std::string &outputBuffer);

}  // namespace crypto

}  // namespace utils