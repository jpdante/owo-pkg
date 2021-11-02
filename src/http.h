#pragma once

#include <indicators/progress_bar.hpp>

class HttpClient {
 public:
  HttpClient();
  ~HttpClient();

 private:
  indicators::ProgressBar* progressBar;

 public:
  bool downloadFile(std::string url, std::string path);

 private:
  double progress(double dltotal, double dlnow, double ultotal, double ulnow);
};