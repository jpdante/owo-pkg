#include "repo.hpp"

#include <filesystem>
#include <fstream>
#include <toml.hpp>

#include "http.hpp"

namespace repo {

RepositoryConfig::RepositoryConfig(std::string name, std::string display_name,
                                   std::string url) {
  this->name = name;
  this->display_name = display_name;
  this->url = url;
  this->path = "";
}

RepositoryConfig* read_repository(std::string file) {
  const auto data = toml::parse(file);
  if (!data.contains("name")) return nullptr;
  if (!data.contains("url")) return nullptr;

  std::string name = toml::find<std::string>(data, "name");
  std::string display_name =
      toml::find_or<std::string>(data, "display_name", name);
  std::string url = toml::find<std::string>(data, "url");

  RepositoryConfig* repo = new RepositoryConfig(name, display_name, url);
  repo->path = file;
  return repo;
};

std::vector<RepositoryConfig*> load_repositories(std::string path) {
  std::vector<RepositoryConfig*> repositories;

  for (const auto& entry : std::filesystem::directory_iterator(path)) {
    if (!entry.is_regular_file()) continue;
    std::filesystem::path entryPath = entry.path();

    RepositoryConfig* config = read_repository(entryPath);
    if (config == nullptr) continue;

    repositories.push_back(config);
  }
  return repositories;
}

bool check_update(RepositoryConfig* repository) {
  HttpClient client;
  std::string hash;
  if (client.download_string(repository->url, hash)) {
    return true;
  }
  std::cout << "Failed to check repository '" << repository->display_name
            << "' at " << repository->url << std::endl;
  return false;
}

bool update_repository(RepositoryConfig* repository, std::string cache_path) {
  HttpClient client;
  std::string url = repository->url + "packages/packages.json";
  std::string fileName = cache_path + "/" + repository->name + ".cr";
  std::cout << "Downloading repository " << repository->display_name << " (" << repository->name << ") at " << url << std::endl;
  return client.download_file(url, fileName);
}

bool save_repository(RepositoryConfig* repository, std::string file) {
  /*nlohmann::json repoData;
    repoData["name"] = repository->name;
    repoData["url"] = repository->url;
    std::fstream stream;
    stream.open(file, std::ios::out | std::ios::trunc);
    stream << repoData;
    stream.close();*/
  return true;
}

}  // namespace repo