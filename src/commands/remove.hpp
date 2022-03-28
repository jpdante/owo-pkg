#pragma once

#include <iostream>
#include <set>

#include "../main.hpp"

namespace owo::commands {

void remove(Cli* cli, std::set<std::string> packagesNames);

}