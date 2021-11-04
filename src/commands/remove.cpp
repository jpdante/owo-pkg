#include "remove.hpp"

#include <iostream>
#include <vector>

#include "../repo.hpp"

namespace cmd {

void remove(Config config, std::set<std::string> packages, bool verbose,
            bool force) {
  std::cout << "Remove" << std::endl;
}

}  // namespace cmd