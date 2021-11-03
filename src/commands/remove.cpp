#include "remove.h"

#include <iostream>

#include "../utils/crypto.h"

namespace cmd {

void remove(std::set<std::string> packages, bool verbose, bool force) {
  std::cout << "Remove" << std::endl;
  std::string data;
  //utils::crypto::sha256_string("Pega no meu pau", data);
  //std::cout << data << std::endl;
}

}  // namespace cmd