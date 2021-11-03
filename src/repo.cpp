#include "repo.hpp"

#include <fstream>
#include <nlohmann/json.hpp>

namespace repo {

RepositoryConfig::RepositoryConfig(std::string name, std::string url) {
  this->name = name;
  this->url = url;
  this->path = "";
}

Repository::Repository() {}

RepositoryConfig* read_repository(std::string file) {
  std::fstream stream;
  stream.open(file, std::ios::in);
  nlohmann::json repoData;
  stream >> repoData;
  stream.close();
  if (!repoData.contains("name") || !repoData["name"].is_string())
    return nullptr;
  if (!repoData.contains("url") || !repoData["url"].is_string()) return nullptr;

  RepositoryConfig* repo =
      new RepositoryConfig(repoData["name"], repoData["url"]);
  repo->path = file;
  return repo;
};

bool save_repository(RepositoryConfig* repository, std::string file) {
  nlohmann::json repoData;
  repoData["name"] = repository->name;
  repoData["url"] = repository->url;
  std::fstream stream;
  stream.open(file, std::ios::out | std::ios::trunc);
  stream << repoData;
  stream.close();
  return true;
}

}  // namespace repo