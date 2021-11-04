#include "install.hpp"

#include <iostream>

#include "../repo.hpp"

namespace cmd {

void install(Config config, std::set<std::string> packages, bool verbose,
             bool force) {
  std::filesystem::path repoConfigPath(config.repo_path);
  std::filesystem::path cachePath(config.cache_path);

  std::vector<repo::RepositoryConfig*> repos =
      repo::load_repositories_configs(repoConfigPath);
  
  repo::CachedRepositories cachedRepositories;
  for (repo::RepositoryConfig* repoConfig : repos) {
    repo::CachedRepository cachedRepository;
    if (repo::load_repository(repos, cachePath, cachedRepository)) {

    }
  cachedRepositories.add_repository
  }
}

}  // namespace cmd