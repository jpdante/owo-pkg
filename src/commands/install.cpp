#include "install.hpp"

#include <iostream>

#include "../repo.hpp"

namespace cmd {

void install(Config config, std::set<std::string> packagesNames, bool verbose, bool force) {
  std::filesystem::path repoConfigPath(config.repo_path);
  std::filesystem::path cachePath(config.cache_path);

  std::vector<repo::RepositoryConfig*> repos = repo::load_repositories_configs(repoConfigPath);

  std::cout << "Reading repositories..." << std::endl;
  repo::CachedRepositories cachedRepositories;
  int count = 0;
  for (repo::RepositoryConfig* repoConfig : repos) {
    count++;
    if (verbose) std::cout << "Reading:" << count << " " << repoConfig->display_name << " (" << repoConfig->name << ")... " << std::flush;
    repo::CachedRepository* cachedRepository;
    if (repo::load_repository(repoConfig, cachePath, &cachedRepository)) {
      cachedRepositories.add_repository(cachedRepository);
      if (verbose) std::cout << "Ok" << std::endl;
    } else {
      if (verbose) std::cout << "Failed" << std::endl;
    }
  }

  std::vector<Package*> packages;
  for (std::string packageName : packagesNames) {
    Package* package = cachedRepositories.get_package(packageName);
    if (package == nullptr) {
      std::cout << "Failed to find package '" << packageName << "'." << std::endl;
      return;
    }
    packages.push_back(package);
  }

  for (Package* package : packages) {
    std::cout << "Installing " << package->repository + ":" + package->name + "@" + package->latest_version << "..." << std::endl;
  }
}

}  // namespace cmd