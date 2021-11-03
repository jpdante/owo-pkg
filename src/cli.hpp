#pragma once

#include <clipp.h>

#include <iostream>

struct Config {
  std::string repo_path;
  std::string cache_path;
};

namespace owo {

void setup_cli(int argc, char* argv[]);

Config load_config(std::string fileName);

void print_usage();

}