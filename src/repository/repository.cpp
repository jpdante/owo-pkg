#include "repository.hpp"

#include <iostream>
#include <memory>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/reader.h>
#include <zlib.h>


#include "../core/crypto.hpp"

namespace owo {

Repository::Repository(core::Logger *logger, RepositoryConfig config,
                       std::filesystem::path configPath,
                       std::filesystem::path cachePath) {
  this->logger = logger;
  this->enabled = config.enabled;
  this->name = config.name;
  this->url = config.url;
  this->supportsCompression = config.supportsCompression;
  this->configPath = configPath;
  this->loaded = false;
  this->cacheFilePath = cachePath / (this->name + ".repo.cache");
  this->packageStream = nullptr;
}

Repository::~Repository() {
  if (this->packageStream != nullptr) {
    this->packageStream->close();
    this->packageStream.reset();
  }
  this->logger->Free();
}

bool Repository::Load() {
  this->loaded = false;
  if (this->packageStream != nullptr) {
    this->packageStream->close();
    this->packageStream.reset();
  }
  if (!std::filesystem::exists(this->cacheFilePath))
    return false;
  this->packageStream = std::make_unique<std::ifstream>(this->cacheFilePath);
  if (this->packageStream) {
    bool isOpen = this->packageStream->is_open();
    if (!isOpen) {
      this->packageStream->close();
    this->packageStream.reset();
    }
    this->loaded = isOpen;
    return isOpen;
  }
  return false;
}

void Repository::Unload() {
  this->loaded = false;
  if (this->packageStream != nullptr) {
    this->packageStream->close();
    this->packageStream.reset();
  }
}

bool Repository::CheckUpdate() {
  core::HttpClient httpClient = core::HttpClient();

  std::string packagesSha256;
  if (!httpClient.DownloadString(this->url + "/packages/Packages.sha256",
                                 packagesSha256)) {
    throw std::runtime_error("Failed to download hash at '" + this->url +
                             "/packages/Packages.sha256" + "'");
  }

  std::string fileSha256;
  if (core::Sha256File(this->cacheFilePath, fileSha256)) {
    return packagesSha256 != fileSha256;
  } else {
    return true;
  }
}

bool Repository::Update() {
  core::HttpClient httpClient = core::HttpClient();
  if (this->supportsCompression) {
    try {
      this->logger->Info("Updating repository " + this->name);
      if (!ClearCache())
        throw std::runtime_error("Failed to delete old cache file at '" +
                                 this->cacheFilePath.generic_string() + "'");
      Download(httpClient, this->supportsCompression);
      return true;
    } catch (std::exception &ex) {
      this->logger->Error(std::string("Exception: ") + ex.what());
      this->logger->Error("Failed to use compression, going to fallback");
    }
  }
  try {
    this->logger->Info("Updating repository " + this->name);

    if (!ClearCache())
      throw std::runtime_error("Failed to delete old cache file at '" +
                               this->cacheFilePath.generic_string() + "'");
    Download(httpClient, false);
    return true;
  } catch (std::exception &ex) {
    this->logger->Error(std::string("Exception: ") + ex.what());
  }
  return false;
}

bool Repository::ClearCache() {
  if (std::filesystem::exists(this->cacheFilePath) &&
      std::filesystem::is_regular_file(this->cacheFilePath)) {
    return std::filesystem::remove(this->cacheFilePath);
  }
  return true;
}

std::list<std::string> Repository::SearchPackages(std::string packages) {
  if (!this->loaded)
    throw std::runtime_error("Repository '" + this->name + "' was not loaded");
  
  this->packageStream->seekg(0, std::ios::beg);
  rapidjson::Document document;
  rapidjson::IStreamWrapper isw(*this->packageStream);
  std::list<std::string> packageList;

  return packageList;
}

void Repository::Download(owo::core::HttpClient httpClient,
                                    bool useCompression) {
  if (useCompression) {
    std::string uri = this->url + "/packages/Packages.gz";
    std::filesystem::path compressedFilePath =
        this->cacheFilePath.concat(".gz");
    if (!httpClient.DownloadFile(uri, compressedFilePath))
      throw std::runtime_error("Failed to download package list at '" + uri +
                               "'");

    gzFile compressedFile =
        gzopen(compressedFilePath.generic_string().c_str(), "r");
    try {
      std::fstream uncompressedFile;
      uncompressedFile.open(this->cacheFilePath,
                            std::ios::out | std::ios::binary | std::ios::trunc);
      if (compressedFile && uncompressedFile.is_open()) {
        char buffer[128];
        int num_read = 0;
        while ((num_read = gzread(compressedFile, buffer, sizeof(buffer))) >
               0) {
          uncompressedFile.write(buffer, num_read);
        }
        gzclose(compressedFile);
        uncompressedFile.close();
        if (std::filesystem::exists(compressedFilePath))
          std::filesystem::remove(compressedFilePath);
      }
    } catch (std::exception &ex) {
      gzclose(compressedFile);
      throw ex;
    }

    std::string packagesSha256;
    uri = this->url + "/packages/Packages.sha256";
    if (!httpClient.DownloadString(uri, packagesSha256))
      throw std::runtime_error("Failed to download hash at '" + uri + "'");

    std::string fileSha256;
    if (core::Sha256File(this->cacheFilePath, fileSha256)) {
      if (packagesSha256 != fileSha256)
        throw std::runtime_error("Hashes don't match");
    } else {
      throw std::runtime_error("Failed to get hash from '" +
                               this->cacheFilePath.generic_string() + "'");
    }
  } else {
    std::string uri = this->url + "/packages/Packages";
    if (!httpClient.DownloadFile(uri, this->cacheFilePath))
      throw std::runtime_error("Failed to download package list at '" + uri +
                               "'");

    std::string packagesSha256;
    uri = this->url + "/packages/Packages.sha256";
    if (!httpClient.DownloadString(uri, packagesSha256))
      throw std::runtime_error("Failed to download hash at '" + uri + "'");

    std::string fileSha256;
    if (core::Sha256File(this->cacheFilePath, fileSha256)) {
      if (packagesSha256 != fileSha256)
        throw std::runtime_error("Hashes don't match");
    } else {
      throw std::runtime_error("Failed to get hash from '" +
                               this->cacheFilePath.generic_string() + "'");
    }
  }
}

void Repository::LoadPackages() {
  rapidjson::Document document;
  rapidjson::IStreamWrapper isw(*this->packageStream);

  while (this->packageStream->peek() != std::ifstream::traits_type::eof()) {
    document.ParseStream<rapidjson::kParseStopWhenDoneFlag>(isw);

    if (document.HasParseError()) {
      logger->Info("Failed to parse package list");
      return;
    }

    logger->Info(document["name"].GetString());
  }
}

} // namespace owo