#pragma once

#include <iostream>
#include <set>

namespace cmd {

void remove(std::set<std::string> packages, bool verbose, bool force);

}