#pragma once

#include <iostream>
#include <filesystem>

namespace owo::core {

void Sha256String(std::string string, std::string &output);
bool Sha256File(std::filesystem::path path, std::string &output);

}  // namespace owo::core