#include "update.hpp"

#include <filesystem>
#include <iostream>
#include <vector>

#include "../http.hpp"
#include "../repo.hpp"

namespace cmd {

void update(Config config, std::set<std::string> packages, bool verbose,
            bool force) {
  std::filesystem::path repoConfigPath(config.repo_path);
  std::filesystem::path cachePath(config.cache_path);

  std::vector<repo::RepositoryConfig*> repos =
      repo::load_repositories(repoConfigPath);
  for (repo::RepositoryConfig* repoConfig : repos) {
    if (repo::check_update(repoConfig, cachePath)) {
      if (!repo::update_repository(repoConfig, cachePath)) {
        std::cout << "Failed to update repository " << repoConfig->display_name
                  << " (" << repoConfig->name << ") at " << repoConfig->url
                  << std::endl;
      }
    }
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