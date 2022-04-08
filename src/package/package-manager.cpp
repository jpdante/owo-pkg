#include "package-manager.hpp"

namespace owo {

PackageManager::PackageManager() {}

PackageManager::~PackageManager() {}

void PackageManager::InstallPackage(Package package) {}
void PackageManager::RemovePackage(Package package) {}
void PackageManager::RepairPackage(Package package) {}
void PackageManager::UpdatePackage(Package package, PackageVersion packageVersion) {}

}  // namespace owo