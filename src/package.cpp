#include "package.hpp"

Package::Package(std::string repository, nlohmann::json value) {
  this->repository = repository;
  if (!value.contains("name"))
    throw std::runtime_error("Json field 'name' not found.");
  if (!value["name"].is_string())
    throw std::runtime_error(
        "Json field 'name' invalid type, expected type string.");
  this->name = value["name"].get<std::string>();

  if (!value.contains("description"))
    throw std::runtime_error("Json field 'description' not found.");
  if (!value["description"].is_string())
    throw std::runtime_error(
        "Json field 'description' invalid type, expected type string.");
  this->description = value["description"].get<std::string>();

  if (!value.contains("tags"))
    throw std::runtime_error("Json field 'tags' not found.");
  if (!value["tags"].is_array())
    throw std::runtime_error(
        "Json field 'tags' invalid type, expected type string array.");
  this->tags = value["tags"].get<std::set<std::string>>();

  if (!value.contains("latest_version"))
    throw std::runtime_error("Json field 'latest_version' not found.");
  if (!value["latest_version"].is_string())
    throw std::runtime_error(
        "Json field 'latest_version' invalid type, expected type string.");
  this->latest_version = value["latest_version"].get<std::string>();
}

PackageVersion::PackageVersion(nlohmann::json value) {}

PackageDependencie::PackageDependencie(nlohmann::json value) {}