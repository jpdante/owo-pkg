#pragma once

#include <iostream>
#include <set>

#include "../cli.hpp"

namespace cmd {

void remove(Config config, std::set<std::string> packages, bool verbose, bool force);

}