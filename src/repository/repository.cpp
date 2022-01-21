#include "repository.hpp"

#include <zlib.h>

#include "../core/crypto.hpp"
#include "../shared.hpp"

namespace owo {

Repository::Repository(RepositoryConfig config, std::filesystem::path configPath) {
  this->enabled = config.enabled;
  this->name = config.name;
  this->url = config.url;
  this->supportsCompression = config.supportsCompression;
  this->configPath = configPath;
  this->loaded = false;
  std::filesystem::path cachePath = std::filesystem::path(Shared::config.cachePath);
  this->cacheFilePath = cachePath / (this->name + ".repo.cache");
  this->packageStream = nullptr;
}

Repository::~Repository() {
  if (this->packageStream != nullptr) {
    this->packageStream->close();
    delete this->packageStream;
  }
}

bool Repository::LoadRepository() {
  if (this->packageStream != nullptr) {
    this->packageStream->close();
    delete this->packageStream;
  }
  this->packageStream = new std::ifstream(this->cacheFilePath);
  bool isOpen = this->packageStream->is_open();
  if (!isOpen) {
    this->packageStream->close();
    delete this->packageStream;
  }
  return isOpen;
}

bool Repository::UpdateRepository(int count = -1) {
  core::HttpClient httpClient = core::HttpClient();
  if (this->supportsCompression) {
    try {
      if (!ClearCache()) throw std::runtime_error("Failed to delete old cache file at '" + this->cacheFilePath.generic_string() + "'");
      DownloadRepository(httpClient, this->supportsCompression);
      return true;
    } catch (std::exception ex) {
      if (count != -1) {
        std::cout << count << ":Exception: " << ex.what() << std::endl;
        std::cout << count << ":Failed to use compression, going to fallback" << std::endl;
      } else {
        std::cout << "Exception: " << ex.what() << std::endl;
        std::cout << "Failed to use compression, going to fallback" << std::endl;
      }
    }
  }
  try {
    if (count != -1) {
      std::cout << count << ":Updating repository" << std::endl;
    } else {
      std::cout << "Updating repository '" + this->name + "'" << std::endl;
    }
    if (!ClearCache()) throw std::runtime_error("Failed to delete old cache file at '" + this->cacheFilePath.generic_string() + "'");
    DownloadRepository(httpClient, false);
    return true;
  } catch (std::runtime_error ex) {
    if (count != -1) {
      std::cout << count << ":Exception: " << ex.what() << std::endl;
    } else {
      std::cout << "Exception: " << ex.what() << std::endl;
    }
  }
  return false;
}

bool Repository::ClearCache() {
  if (std::filesystem::exists(this->cacheFilePath) && std::filesystem::is_regular_file(this->cacheFilePath)) {
    return std::filesystem::remove(this->cacheFilePath);
  }
  return true;
}

std::list<std::string> Repository::SearchPackages(std::string packages) {
  if (!this->loaded) throw std::runtime_error("Repository '" + this->name + "' was not loaded");
  std::list<std::string> packageList;
  return packageList;
}

void Repository::DownloadRepository(owo::core::HttpClient httpClient, bool useCompression) {
  if (useCompression) {
    std::string uri = this->url + "/packages/Packages.gz";
    std::filesystem::path compressedFilePath = this->cacheFilePath.concat(".gz");
    if (!httpClient.DownloadFile(uri, compressedFilePath)) throw std::runtime_error("Failed to download package list at '" + uri + "'");

    gzFile compressedFile = gzopen(compressedFilePath.generic_string().c_str(), "r");
    try {
      std::fstream uncompressedFile;
      uncompressedFile.open(this->cacheFilePath, std::ios::out | std::ios::binary | std::ios::trunc);
      if (compressedFile && uncompressedFile.is_open()) {
        char buffer[128];
        int num_read = 0;
        while ((num_read = gzread(compressedFile, buffer, sizeof(buffer))) > 0) {
          uncompressedFile.write(buffer, num_read);
        }
        gzclose(compressedFile);
        uncompressedFile.close();
        if (std::filesystem::exists(compressedFilePath)) std::filesystem::remove(compressedFilePath);
      }
    } catch (std::exception ex) {
      gzclose(compressedFile);
      throw ex;
    }

    std::string packagesSha256;
    uri = this->url + "/packages/Packages.sha256";
    if (!httpClient.DownloadString(uri, packagesSha256)) throw std::runtime_error("Failed to download hash at '" + uri + "'");

    std::string fileSha256;
    if (core::Sha256File(this->cacheFilePath, fileSha256)) {
      if (packagesSha256 != fileSha256) throw std::runtime_error("Hashes don't match");
    } else {
      throw std::runtime_error("Failed to get hash from '" + this->cacheFilePath.generic_string() + "'");
    }
  } else {
    std::string uri = this->url + "/packages/Packages";
    if (!httpClient.DownloadFile(uri, this->cacheFilePath)) throw std::runtime_error("Failed to download package list at '" + uri + "'");

    std::string packagesSha256;
    uri = this->url + "/packages/Packages.sha256";
    if (!httpClient.DownloadString(uri, packagesSha256)) throw std::runtime_error("Failed to download hash at '" + uri + "'");

    std::string fileSha256;
    if (core::Sha256File(this->cacheFilePath, fileSha256)) {
      if (packagesSha256 != fileSha256) throw std::runtime_error("Hashes don't match");
    } else {
      throw std::runtime_error("Failed to get hash from '" + this->cacheFilePath.generic_string() + "'");
    }
  }
}

}  // namespace owo