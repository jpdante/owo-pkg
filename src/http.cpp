#include "http.h"

#include <math.h>

#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/cURLpp.hpp>
#include <fstream>
#include <indicators/cursor_control.hpp>
#include <indicators/progress_bar.hpp>
#include <iostream>

HttpClient::HttpClient() {
  progressBar = new indicators::ProgressBar{
      indicators::option::BarWidth{50},
      indicators::option::Start{" ["},
      indicators::option::Fill{"█"},
      indicators::option::Lead{"█"},
      indicators::option::Remainder{"-"},
      indicators::option::End{"]"},
      indicators::option::PrefixText{"Downloading"},
      indicators::option::ForegroundColor{indicators::Color::grey},
      indicators::option::ShowElapsedTime{true},
      indicators::option::ShowRemainingTime{true},
      indicators::option::ShowPercentage{true},
      indicators::option::FontStyles{
          std::vector<indicators::FontStyle>{indicators::FontStyle::bold}}};
}

bool HttpClient::downloadFile(std::string url, std::string path) {
  try {
    curlpp::Cleanup myCleanup;
    curlpp::Easy request;
    std::fstream myfile;
    myfile.open(path, std::ios::in | std::ios::out | std::ios::binary |
                          std::ios::trunc);

    indicators::show_console_cursor(false);

    request.setOpt(curlpp::options::Url(url));
    request.setOpt(curlpp::options::WriteStream(&myfile));
    request.setOpt(curlpp::options::Verbose(false));
    request.setOpt(curlpp::options::NoProgress(0));
    request.setOpt(curlpp::options::ProgressFunction(std::bind(
        &HttpClient::progress, this, std::placeholders::_1,
        std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)));
    request.perform();

    std::cout << "Complete!" << std::endl;
    indicators::show_console_cursor(true);
    return true;
  } catch (curlpp::RuntimeError& e) {
    indicators::show_console_cursor(true);
    std::cout << e.what() << std::endl;
  } catch (curlpp::LogicError& e) {
    indicators::show_console_cursor(true);
    std::cout << e.what() << std::endl;
  }
  return false;
}

double HttpClient::progress(double dltotal, double dlnow, double ultotal,
                            double ulnow) {
  if (dltotal == 0 && dlnow == 0) return 0;
  double progress = (dlnow / dltotal) * 100;
  int percent = floorf(progress * 100) / 100;
  // std::cout << percent << "%" << std::endl;
  if (progressBar->current() == percent) return 0;
  progressBar->set_progress((int)percent);
  return 0;
}