#include "search.hpp"

#include <iostream>

namespace owo::commands {

void search(Cli* cli, std::set<std::string> packagesNames) {
  /*try {
    RepositoryManager repoManager = RepositoryManager(Shared::config.repositoryPath, Shared::config.cachePath);

    std::list<std::string> foundPackages;
    for (auto repository : repoManager.GetRepositories()) {
      if (!repository->LoadRepository()) throw std::runtime_error("Repository '" + repository->name + "' cannot be loaded, try to update the repository.");
      for (auto package : packages) {
        for (auto foundPackage : repository->SearchPackages(package)) {
          foundPackages.push_back(foundPackage);
        }
      }
    }

    for (auto package : foundPackages) {
      std::cout << package << std::endl;
    }
  } catch (std::exception ex) {
    std::cout << "Exception: " << ex.what() << std::endl;
  }*/

  /*std::filesystem::path repoConfigPath(config.repo_path);
  std::filesystem::path cachePath(config.cache_path);

  std::vector<repo::RepositoryConfig*> repos = repo::load_repositories_configs(repoConfigPath);

  std::cout << "Reading repositories... ";
  if (verbose)
    std::cout << std::endl;
  else
    std::cout << std::flush;
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

  if (!verbose) std::cout << "Ok" << std::endl;

  std::set<Package*> results;
  for (std::string string : packages) {
    std::set<Package*> result = cachedRepositories.search_package(string);
    for (Package* pkg : result) {
      results.insert(pkg);
    }
  }

  std::cout << "Found " << results.size() << " packages."
            << "\n";
  for (Package* pkg : results) {
    std::cout << pkg->repository << ":" << pkg->name << "\n" << pkg->description << "\n\n";
  }
  std::cout << std::flush;*/
}

}  // namespace owo::commands