#pragma once

#include <clipp.h>

#include <iostream>

#include "../shared.hpp"

namespace owo::core {

void setup_cli(int argc, char* argv[]);

Config load_config(std::string fileName);

void print_usage();

}  // namespace owo::core