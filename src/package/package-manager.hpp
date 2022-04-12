#pragma once

#include <set>

#include "../repository/repository-manager.hpp"
#include "package.hpp"

namespace owo {

class PackageManager {
 public:
  PackageManager(RepositoryManager* repositoryManager);
  ~PackageManager();

 private:
  RepositoryManager* repositoryManager;

 public:
  void InstallPackage(Package package);
  std::set<Package*> SearchPackages(std::string search);
  std::set<PackageVersion*> FindPackageVersion(std::string name, std::string version);
  std::set<PackageVersion*> BuildInstallTree(PackageVersion* packageVersion);
  void RemovePackage(Package package);
  void RepairPackage(Package package);
  void UpdatePackage(Package package, PackageVersion packageVersion);
};

}  // namespace owo