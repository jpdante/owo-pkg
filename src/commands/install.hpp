#pragma once

#include <iostream>
#include <set>

#include "../cli.hpp"

namespace cmd {

void install(Config config, std::set<std::string> packagesNames, bool verbose,
             bool force);

}