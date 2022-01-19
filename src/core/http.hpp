#pragma once

#include <filesystem>
#include <indicators/progress_bar.hpp>

namespace owo::core {

class HttpClient {
 public:
  HttpClient(bool showProgressBar = false);
  ~HttpClient();

 private:
  indicators::ProgressBar* progressBar;

 public:
  bool DownloadString(std::string url, std::string& data);
  bool DownloadFile(std::string url, std::filesystem::path path);

 private:
  double progress(double dltotal, double dlnow, double ultotal, double ulnow);
};

}  // namespace owo::core