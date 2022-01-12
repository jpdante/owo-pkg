#pragma once

#include <indicators/progress_bar.hpp>

namespace owo::core {

class HttpClient {
 public:
  HttpClient(bool showProgressBar = false);
  ~HttpClient();

 private:
  indicators::ProgressBar* progressBar;

 public:
  bool download_string(std::string url, std::string& data);
  bool download_file(std::string url, std::string path);

 private:
  double progress(double dltotal, double dlnow, double ultotal, double ulnow);
};

}  // namespace owo::core