#pragma once

#include <iostream>
#include <set>

namespace cmd {

void install(std::set<std::string> packages, bool verbose, bool force);

}