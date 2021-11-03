#pragma once

#include <iostream>
#include <set>
#include <vector>

class PackageDependencie {
 public:
  PackageDependencie();

 public:
  std::string name;
  std::string version;
};

class PackageVersion {
 public:
  PackageVersion();

 public:
  std::string version;
  std::string branch;
  std::string arch;
  std::string os;
  std::string file;
  std::string hash;
  std::set<PackageDependencie> dependencies;
};

class Package {
 public:
  Package();

 public:
  std::string name;
  std::string description;
  std::set<std::string> tags;
  std::vector<PackageVersion> versions;
  std::string latest_version;
};