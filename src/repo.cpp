#include "repo.h"

#include <fstream>
#include <nlohmann/json.hpp>

Repository::Repository(std::string name, std::string url) {
  Name = name;
  Url = url;
  Path = "";
}

Repository* read_repository(std::string file) {
  std::fstream stream;
  stream.open(file, std::ios::in);
  nlohmann::json repoData;
  stream >> repoData;
  stream.close();
  if (!repoData.contains("name") || !repoData["name"].is_string())
    return nullptr;
  if (!repoData.contains("url") || !repoData["url"].is_string()) return nullptr;

  Repository* repo = new Repository(repoData["name"], repoData["url"]);
  repo->Path = file;
  return repo;
};

bool save_repository(Repository* repository, std::string file) {
  nlohmann::json repoData;
  repoData["name"] = repository->Name;
  repoData["url"] = repository->Url;
  std::fstream stream;
  stream.open(file, std::ios::out | std::ios::trunc);
  stream << repoData;
  stream.close();
  return true;
}