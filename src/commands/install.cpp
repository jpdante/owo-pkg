#include "install.hpp"

#include <iostream>

namespace owo::commands {

void install(std::set<std::string> packagesNames) {
  /*std::filesystem::path repoConfigPath(config.repo_path);
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

  std::vector<Package*> found_packages;
  for (std::string packageName : packagesNames) {
    Package* package = cachedRepositories.get_package(packageName);
    if (package == nullptr) {
      std::cout << "Failed to find package '" << packageName << "'." << std::endl;
      return;
    }
    found_packages.push_back(package);
  }

  std::queue<Package*> download_packages;
  std::queue<Package*> install_packages;
  for (Package* package : found_packages) {
    std::cout << "Installing " << package->repository + ":" + package->name + "@" + package->latest_version << "..." << std::endl;
  }*/
}

/*void add_package(std::queue<Package*> queue, Package* package) {
  for (Package* package : package.) {
    std::cout << "Installing " << package->repository + ":" + package->name + "@" + package->latest_version << "..." << std::endl;
  }
}*/

}  // namespace owo::commands