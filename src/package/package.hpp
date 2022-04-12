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

class Package;
class PackageVersion {
 public:
  PackageVersion(Package* package, nlohmann::json value);
  ~PackageVersion();

 public:
  Package* package;
  std::string version;
  std::string branch;
  std::string arch;
  std::string os;
  std::string file;
  std::string hash;
  std::vector<PackageDependencie*> dependencies;
};

class Package {
 public:
  Package(nlohmann::json value);
  ~Package();

 public:
  std::string name;
  std::string description;
  std::set<std::string> tags;
  std::vector<PackageVersion*> versions;
  std::string latest_version;
};

}