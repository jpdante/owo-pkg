#pragma once

#include <iostream>

namespace owo::core {

void sha256_string(std::string string, std::string &output);
bool sha256_file(std::string path, std::string &output);

}  // namespace owo::core