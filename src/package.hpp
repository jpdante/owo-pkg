#pragma once

#include <iostream>
#include <set>
#include <vector>
#include <nlohmann/json.hpp>

class PackageDependencie {
 public:
  PackageDependencie(nlohmann::json value);

 public:
  std::string name;
  std::string version;
};

class PackageVersion {
 public:
  PackageVersion(nlohmann::json value);

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
  Package(std::string repository, nlohmann::json value);

 public:
  std::string repository;
  std::string name;
  std::string description;
  std::set<std::string> tags;
  std::vector<PackageVersion> versions;
  std::string latest_version;
};