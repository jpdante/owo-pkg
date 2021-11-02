#pragma once

#include <iostream>
#include <set>

class Package {
 public:
  Package();

 public:
  std::string name;
  std::string description;
  std::set<std::string> tags;
};

class PackageDependencie {
 public:
  PackageDependencie();

 public:
  std::string name;
  std::string version;
  std::string latest_version;
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