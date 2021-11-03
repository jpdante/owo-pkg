#include "update.hpp"

#include <iostream>
#include <vector>

#include "../http.hpp"
#include "../repo.hpp"

namespace cmd {

void update(Config config, std::set<std::string> packages, bool verbose,
            bool force) {
  std::vector<repo::RepositoryConfig*> repos = repo::load_repositories(config.repo_path);
  for (repo::RepositoryConfig* repo : repos) {
    repo::update_repository(repo, config.cache_path);
  }

  if (packages.size() > 0) {
    // Update packages
  } else {
    // Update all
  }
  std::cout << "" << std::endl;
  std::cout << verbose << std::endl;
}

}  // namespace cmd