#pragma once

#include <iostream>
#include <set>

#include "../main.hpp"
#include "../repository/repository-manager.hpp"

namespace owo::commands {

void search(Cli* cli, std::set<std::string> packagesNames);

}