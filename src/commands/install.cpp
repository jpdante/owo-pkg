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

  std::cout << "Reading repositories..." << std::endl;
  repo::CachedRepositories cachedRepositories;
  int count = 0;
  for (repo::RepositoryConfig* repoConfig : repos) {
    count++;
    if (verbose)
      std::cout << "Reading:" << count << " " << repoConfig->display_name << " (" << repoConfig->name << ")... "
                << std::flush;
    repo::CachedRepository* cachedRepository;
    if (repo::load_repository(repoConfig, cachePath, &cachedRepository)) {
      cachedRepositories.add_repository(cachedRepository);
      if (verbose) std::cout << "Ok" << std::endl;
    } else {
      if (verbose) std::cout << "Failed" << std::endl;
    }
  }
}

}  // namespace cmd