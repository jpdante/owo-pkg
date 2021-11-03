#include "remove.hpp"

#include <iostream>

#include "../utils/crypto.hpp"

namespace cmd {

void remove(std::set<std::string> packages, bool verbose, bool force) {
  std::cout << "Remove" << std::endl;
  std::string data;
  utils::crypto::sha256_file("/home/jpdante/Desktop/Test", data);
  std::cout << data << std::endl;
}

}  // namespace cmd