#pragma once

#include <iostream>
#include <set>

#include "../cli.hpp"

namespace cmd {

void search(Config config, std::set<std::string> packages, bool verbose,
            bool force);

}