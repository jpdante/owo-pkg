#pragma once

#include <iostream>
#include <set>

#include "../core/cli.hpp"
#include "../repository/repository-manager.hpp"

namespace owo::commands {

void search(std::set<std::string> packages);
    
}