#include "update.hpp"

#include <iostream>

namespace cmd {

void update(std::set<std::string> packages, bool verbose, bool force) {
  if (packages.size() > 0) {
    // Update packages
  } else {
    // Update all
  }
  std::cout << "" << std::endl;
  std::cout << verbose << std::endl;
}

}  // namespace cmd