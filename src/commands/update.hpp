#pragma once

#include <iostream>
#include <set>

#include "../core/cli.hpp"
#include "../repository/repository-manager.hpp"

namespace owo::commands {

void update(std::set<std::string> packages);

}