#include "package-manager.hpp"

namespace owo {

PackageManager::PackageManager(RepositoryManager* repositoryManager) { this->repositoryManager = repositoryManager; }

PackageManager::~PackageManager() {}

void PackageManager::InstallPackage(Package package) {}

std::set<Package*> PackageManager::SearchPackages(std::string search) {
  std::set<Package*> packages;
  for (Repository* repository : repositoryManager->GetRepositories()) {
    repository->SearchPackages(search);
  }
  return packages;
}

std::set<PackageVersion*> PackageManager::FindPackageVersion(std::string name, std::string version) {
  std::set<PackageVersion*> packageVersions;
  for (Package* package : SearchPackages(name + "@" + version)) {
    for (PackageVersion* packageVersion : package->versions) {
      if (packageVersion->version != version) continue;
      packageVersions.insert(packageVersion);
      break;
    }
  }
  if (packageVersions.size() == 0) throw std::runtime_error("Failed to find dependency " + name + "@" + version);
  return packageVersions;
}

std::set<PackageVersion*> PackageManager::BuildInstallTree(PackageVersion* packageVersion) {
  std::set<PackageVersion*> packages;
  for (PackageDependencie* dependency : packageVersion->dependencies) {
    for (PackageVersion* packageVersion : FindPackageVersion(dependency->name, dependency->version)) {
      for (PackageVersion* subDependency : BuildInstallTree(packageVersion)) {
        packages.insert(subDependency);
      }
      break;
    }
  }
  packages.insert(packageVersion);
  return packages;
}

void PackageManager::RemovePackage(Package package) {}

void PackageManager::RepairPackage(Package package) {}

void PackageManager::UpdatePackage(Package package, PackageVersion packageVersion) {}

}  // namespace owo