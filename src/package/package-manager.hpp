#pragma once

#include "package.hpp"

namespace owo {

class PackageManager {
 public:
  PackageManager();
  ~PackageManager();

 public:
  void InstallPackage(Package package);
  void RemovePackage(Package package);
  void RepairPackage(Package package);
  void UpdatePackage(Package package, PackageVersion packageVersion);
};

}  // namespace owo