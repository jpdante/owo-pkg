#pragma once

#include <nlohmann/json.hpp>
#include <set>

namespace owo {

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
  std::vector<PackageDependencie> dependencies;
};

class Package {
 public:
  Package(nlohmann::json value);

 public:
  std::string name;
  std::string description;
  std::set<std::string> tags;
  std::vector<PackageVersion> versions;
  std::string latest_version;
};

}