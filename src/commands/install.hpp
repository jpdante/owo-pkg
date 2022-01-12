#pragma once

#include <iostream>
#include <queue>
#include <set>

#include "../core/cli.hpp"

namespace owo::commands {

void install(std::set<std::string> packagesNames);

// void add_package(std::queue<Package*> queue, Package* package);

}  // namespace owo::commands