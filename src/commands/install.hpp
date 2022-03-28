#pragma once

#include <iostream>
#include <queue>
#include <set>

#include "../main.hpp"

namespace owo::commands {

void install(Cli* cli, std::set<std::string> packagesNames);

}  // namespace owo::commands