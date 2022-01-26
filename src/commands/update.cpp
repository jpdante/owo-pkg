#include "update.hpp"

#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "../core/crypto.hpp"

namespace owo::commands {

void update(std::set<std::string> packages) {
  RepositoryManager repoManager = RepositoryManager(Shared::config.repositoryPath, Shared::config.cachePath);

  int count = 1;
  for (auto repository : repoManager.GetRepositories()) {
    std::string prefix = std::to_string(count) + ":";
    try {
      std::cout << prefix << "Checking " << repository->name << " for updates" << std::endl;
      if (repository->CheckUpdate(prefix)) { repository->UpdateRepository(prefix); }
    } catch (std::exception ex) {
      std::cout << prefix << "Failed to update " << repository->name << std::endl;
    }
    count++;
  }

  /*std::filesystem::path repoConfigPath(config.repo_path);
  std::filesystem::path cachePath(config.cache_path);

  std::vector<repo::RepositoryConfig*> repositoryConfigs =
      repo::load_repositories_configs(repoConfigPath);

  std::vector<repo::RepositoryConfig*> updateRepositories;

  for (repo::RepositoryConfig* repoConfig : repositoryConfigs) {
    std::cout << "Checking:" << repoConfig->id << " "
              << repoConfig->display_name << " (" << repoConfig->name << ")...";
    if (verbose)
      std::cout << std::endl;
    else
      std::cout << std::flush;
    if (repo::check_update(repoConfig, cachePath, verbose)) {
      if (verbose)
        std::cout << "Update:" << repoConfig->id << std::endl;
      else
        std::cout << "Update" << std::endl;
      updateRepositories.push_back(repoConfig);
    } else {
      if (verbose)
        std::cout << "Ok:" << repoConfig->id << std::endl;
      else
        std::cout << "Ok" << std::endl;
    }
  }

  for (repo::RepositoryConfig* repoConfig : updateRepositories) {
    std::cout << "Updating:" << repoConfig->id << " "
              << repoConfig->display_name << " (" << repoConfig->name << ")..."
              << std::endl;
    repo::update_repository(repoConfig, cachePath);
  }

  if (packages.size() > 0) {
    // Update packages
  } else {
    // Update all
  }*/
}

}  // namespace owo::commands