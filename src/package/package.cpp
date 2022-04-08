#include "package.hpp"

namespace owo {

PackageDependencie::PackageDependencie(nlohmann::json value) {
  if (!value.contains("name")) throw std::runtime_error("Json field 'name' not found.");
  if (!value["name"].is_string()) throw std::runtime_error("Json field 'name' invalid type, expected type string.");
  this->name = value["name"].get<std::string>();

  if (!value.contains("version")) throw std::runtime_error("Json field 'version' not found.");
  if (!value["version"].is_string()) throw std::runtime_error("Json field 'version' invalid type, expected type string.");
  this->version = value["version"].get<std::string>();
}

PackageVersion::PackageVersion(nlohmann::json value) {
  if (!value.contains("version")) throw std::runtime_error("Json field 'version' not found.");
  if (!value["version"].is_string()) throw std::runtime_error("Json field 'version' invalid type, expected type string.");
  this->version = value["version"].get<std::string>();

  if (!value.contains("branch")) throw std::runtime_error("Json field 'branch' not found.");
  if (!value["branch"].is_string()) throw std::runtime_error("Json field 'branch' invalid type, expected type string.");
  this->branch = value["branch"].get<std::string>();

  if (!value.contains("arch")) throw std::runtime_error("Json field 'arch' not found.");
  if (!value["arch"].is_string()) throw std::runtime_error("Json field 'arch' invalid type, expected type string.");
  this->arch = value["arch"].get<std::string>();

  if (!value.contains("os")) throw std::runtime_error("Json field 'os' not found.");
  if (!value["os"].is_string()) throw std::runtime_error("Json field 'os' invalid type, expected type string.");
  this->os = value["os"].get<std::string>();

  if (!value.contains("file")) throw std::runtime_error("Json field 'file' not found.");
  if (!value["file"].is_string()) throw std::runtime_error("Json field 'file' invalid type, expected type string.");
  this->file = value["file"].get<std::string>();

  if (!value.contains("hash")) throw std::runtime_error("Json field 'hash' not found.");
  if (!value["hash"].is_string()) throw std::runtime_error("Json field 'hash' invalid type, expected type string.");
  this->hash = value["hash"].get<std::string>();

  if (!value.contains("dependencies")) throw std::runtime_error("Json field 'dependencies' not found.");
  if (!value["dependencies"].is_array()) throw std::runtime_error("Json field 'dependencies' invalid type, expected type json array.");
  for (auto sub : value["dependencies"]) {
    this->dependencies.push_back(PackageDependencie(sub));
  }
}

Package::Package(nlohmann::json value) {
  if (!value.contains("name")) throw std::runtime_error("Json field 'name' not found.");
  if (!value["name"].is_string()) throw std::runtime_error("Json field 'name' invalid type, expected type string.");
  this->name = value["name"].get<std::string>();

  if (!value.contains("description")) throw std::runtime_error("Json field 'description' not found.");
  if (!value["description"].is_string()) throw std::runtime_error("Json field 'description' invalid type, expected type string.");
  this->description = value["description"].get<std::string>();

  if (!value.contains("tags")) throw std::runtime_error("Json field 'tags' not found.");
  if (!value["tags"].is_array()) throw std::runtime_error("Json field 'tags' invalid type, expected type string array.");
  this->tags = value["tags"].get<std::set<std::string>>();

  if (!value.contains("versions")) throw std::runtime_error("Json field 'versions' not found.");
  if (!value["versions"].is_array()) throw std::runtime_error("Json field 'versions' invalid type, expected type json array.");
  for (auto sub : value["versions"]) {
    this->versions.push_back(PackageVersion(sub));
  }

  if (!value.contains("latest_version")) throw std::runtime_error("Json field 'latest_version' not found.");
  if (!value["latest_version"].is_string()) throw std::runtime_error("Json field 'latest_version' invalid type, expected type string.");
  this->latest_version = value["latest_version"].get<std::string>();
}

}  // namespace owo