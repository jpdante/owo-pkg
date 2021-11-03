#include "remove.hpp"

#include <iostream>
#include <vector>

#include "../repo.hpp"
#include "../utils/crypto.hpp"

namespace cmd {

void remove(Config config, std::set<std::string> packages, bool verbose,
            bool force) {
  std::cout << "Remove" << std::endl;
  std::vector<repo::RepositoryConfig*> repos = repo::load_repositories(config.repo_path);
  // std::string data;
  // utils::crypto::sha256_file("/home/jpdante/Desktop/Test", data);
  // std::cout << data << std::endl;
}

}  // namespace cmd