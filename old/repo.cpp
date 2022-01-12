#include "repo.hpp"

#include <zlib.h>

#include <fstream>
#include <toml.hpp>

#include "http.hpp"
#include "utils/crypto.hpp"

namespace repo {

// RepositoryConfig

RepositoryConfig::RepositoryConfig() {
  this->name = "";
  this->display_name = "";
  this->url = "";
  this->config_path = "";
  this->config_fileName = "";
  this->support_compression = false;
}

// End RepositoryConfig

// CachedRepository

CachedRepository::CachedRepository(RepositoryConfig* config, nlohmann::json value) {
  this->config = config;
  if (!value.contains("packages")) throw std::runtime_error("Json field 'packages' not found.");
  if (!value["packages"].is_array()) throw std::runtime_error("Json field 'packages' invalid type, expected type object array.");
  nlohmann::json pkgs = value["packages"];
  for (nlohmann::json::iterator it = pkgs.begin(); it != pkgs.end(); ++it) {
    this->packages.insert(new Package(config->name, *it));
  }
}

// End CachedRepository

// CachedRepositories

CachedRepositories::CachedRepositories() {}

void CachedRepositories::add_repository(CachedRepository* repo) { this->cached_repositories.insert(repo); }

std::set<Package*> CachedRepositories::search_package(std::string value) {
  std::string searchData;
  std::string repositoryName;

  if (value.find(':') != std::string::npos) {
    int pos = value.find_first_of(':');
    searchData = value.substr(pos + 1);
    repositoryName = value.substr(0, pos);
  } else {
    searchData = value;
    repositoryName = "";
  }

  std::set<Package*> results;
  for (const CachedRepository* repo : this->cached_repositories) {
    if (!repositoryName.empty() && repo->config->name != repositoryName) continue;
    for (Package* package : repo->packages) {
      if (package->name.find(searchData) != std::string::npos) {
        results.insert(package);
        continue;
      }
      if (package->tags.find(searchData) != package->tags.end()) {
        results.insert(package);
        continue;
      }
    }
  }
  return results;
}

Package* CachedRepositories::get_package(std::string value) {
  std::string repositoryName;
  std::string packageName;

  if (value.find(':') != std::string::npos) {
    int pos = value.find_first_of(':');
    packageName = value.substr(pos + 1);
    repositoryName = value.substr(0, pos);
  } else {
    packageName = value;
    repositoryName = "";
  }

  for (const CachedRepository* repo : this->cached_repositories) {
    if (!repositoryName.empty() && repo->config->name != repositoryName) continue;
    for (Package* package : repo->packages) {
      if (package->name == packageName) {
        return package;
      }
    }
  }
  return nullptr;
}

// End CachedRepositories

RepositoryConfig* read_repository_config(std::filesystem::path filePath) {
  const auto data = toml::parse(filePath);
  if (!data.contains("name")) return nullptr;
  if (!data.contains("url")) return nullptr;

  std::string name = toml::find<std::string>(data, "name");
  std::string display_name = toml::find_or<std::string>(data, "display_name", name);
  std::string url = toml::find<std::string>(data, "url");
  bool support_compression = toml::find_or<bool>(data, "support_compression", false);

  RepositoryConfig* repository = new RepositoryConfig();
  repository->name = name;
  repository->display_name = display_name;
  repository->url = url;
  repository->config_path = filePath.generic_string();
  repository->config_fileName = filePath.filename().generic_string();
  repository->support_compression = support_compression;
  return repository;
};

std::vector<RepositoryConfig*> load_repositories_configs(std::filesystem::path dirPath) {
  std::vector<RepositoryConfig*> repositories;

  int count = 0;
  for (const auto& entry : std::filesystem::directory_iterator(dirPath)) {
    if (!entry.is_regular_file()) continue;
    std::filesystem::path entryPath = entry.path();

    RepositoryConfig* config = read_repository_config(entryPath);
    if (config == nullptr) continue;
    count++;
    config->id = count;

    repositories.push_back(config);
  }
  return repositories;
}

bool load_repository(RepositoryConfig* repoConfig, std::filesystem::path cachePath, CachedRepository** cached) {
  std::filesystem::path repoCachePath = cachePath / std::filesystem::path(repoConfig->name + ".rpi");
  if (!std::filesystem::exists(repoCachePath)) return false;
  nlohmann::json value;
  std::fstream cacheFile;
  cacheFile.open(repoCachePath, std::ios::in);
  cacheFile >> value;
  cacheFile.close();
  *cached = new CachedRepository(repoConfig, value);
  return true;
}

bool check_update(RepositoryConfig* repoConfig, std::filesystem::path cachePath, bool verbose) {
  std::string url = repoConfig->url + "packages/packages.sha256";
  std::filesystem::path repoCachePath = cachePath / std::filesystem::path(repoConfig->name + ".rpi");
  std::string localHash;
  std::string remoteHash;

  if (std::filesystem::exists(repoCachePath)) {
    utils::crypto::sha256_file(repoCachePath.generic_string(), localHash);
  } else {
    if (verbose) std::cout << "Repository " << repoConfig->display_name << " (" << repoConfig->name << ") cache not found." << std::endl;
    return true;
  }

  HttpClient client;
  if (client.download_string(url, remoteHash)) {
    if (verbose) std::cout << repoConfig->display_name << " (" << repoConfig->name << ") local hash: " << localHash << std::endl;
    if (verbose) std::cout << repoConfig->display_name << " (" << repoConfig->name << ") remote hash: " << remoteHash << std::endl;
    return localHash != remoteHash;
  }
  std::cout << "Failed to check repository " << repoConfig->display_name << " (" << repoConfig->name << ") at " << repoConfig->url << std::endl;
  return false;
}

bool update_repository(RepositoryConfig* repoConfig, std::filesystem::path cachePath) {
  HttpClient client(true);
  std::string url;
  std::filesystem::path fileName;
  if (repoConfig->support_compression) {
    url = repoConfig->url + "packages/packages.json.gz";
    fileName = cachePath / std::filesystem::path(repoConfig->name + ".rpi.gz");
    if (std::filesystem::exists(fileName)) std::filesystem::remove(fileName);
    std::cout << "Downloading:" << repoConfig->id << " " << repoConfig->display_name << " (" << repoConfig->name << ") at " << url << std::endl;
    if (client.download_file(url, fileName.generic_string())) {
      gzFile compressedFile = gzopen(fileName.generic_string().c_str(), "rb");
      std::fstream uncompressedFile;
      std::filesystem::path uncompressedFileName = cachePath / std::filesystem::path(repoConfig->name + ".rpi");
      if (std::filesystem::exists(uncompressedFileName)) std::filesystem::remove(uncompressedFileName);
      uncompressedFile.open(uncompressedFileName, std::ios::out | std::ios::binary | std::ios::trunc);
      try {
        if (compressedFile && uncompressedFile.is_open()) {
          char buffer[128];
          int num_read = 0;
          while ((num_read = gzread(compressedFile, buffer, sizeof(buffer))) > 0) {
            uncompressedFile.write(buffer, num_read);
          }
          gzclose(compressedFile);
          uncompressedFile.close();
          if (std::filesystem::exists(fileName)) std::filesystem::remove(fileName);
          return true;
        }
      } catch (...) {
        std::cout << "Failed to decompress file, going to fallback." << std::endl;
      }
      gzclose(compressedFile);
      uncompressedFile.close();
      try {
        if (std::filesystem::exists(uncompressedFileName)) std::filesystem::remove(uncompressedFileName);
      } catch (...) {
        std::cout << "Failed to delete cache files." << std::endl;
        std::cout << "File: " << fileName << std::endl;
        std::cout << "File: " << uncompressedFileName << std::endl;
      }
    } else {
      std::cout << "Failed to download, going to fallback." << std::endl;
      if (std::filesystem::exists(fileName)) std::filesystem::remove(fileName);
    }
  }
  url = repoConfig->url + "packages/packages.json";
  fileName = cachePath / std::filesystem::path(repoConfig->name + ".rpi");
  if (std::filesystem::exists(fileName)) std::filesystem::remove(fileName);
  std::cout << "Downloading:" << repoConfig->id << " " << repoConfig->display_name << " (" << repoConfig->name << ") at " << url << std::endl;
  if (client.download_file(url, fileName.generic_string())) {
    return true;
  } else {
    std::cout << "Failed to download repository " << repoConfig->display_name << " (" << repoConfig->name << ") at " << url << std::endl;
    if (std::filesystem::exists(fileName)) std::filesystem::remove(fileName);
  }
  return false;
}

}  // namespace repo