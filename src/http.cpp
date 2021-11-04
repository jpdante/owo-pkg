#include "http.hpp"

#include <math.h>

#include <curlpp/Easy.hpp>
#include <curlpp/Infos.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/cURLpp.hpp>
#include <fstream>
#include <indicators/cursor_control.hpp>
#include <indicators/progress_bar.hpp>
#include <iostream>
#include <sstream>

HttpClient::HttpClient() {
  progressBar = new indicators::ProgressBar{
      indicators::option::BarWidth{50},
      indicators::option::Start{" ["},
      indicators::option::Fill{"█"},
      indicators::option::Lead{"█"},
      indicators::option::Remainder{"-"},
      indicators::option::End{"]"},
      indicators::option::PrefixText{"Downloading"},
      indicators::option::ForegroundColor{indicators::Color::green},
      indicators::option::ShowElapsedTime{true},
      indicators::option::ShowRemainingTime{true},
      indicators::option::ShowPercentage{true},
      indicators::option::FontStyles{
          std::vector<indicators::FontStyle>{indicators::FontStyle::bold}}};
}

HttpClient::~HttpClient() { delete progressBar; }

bool HttpClient::download_string(std::string url, std::string& data) {
  try {
    curlpp::Cleanup myCleanup;
    curlpp::Easy request;
    std::ostringstream response;

    indicators::show_console_cursor(false);

    request.setOpt(curlpp::options::Url(url));
    request.setOpt(curlpp::options::WriteStream(&response));
    request.setOpt(curlpp::options::Verbose(false));
    request.setOpt(curlpp::options::NoProgress(0));
    request.setOpt(curlpp::options::ProgressFunction(std::bind(
        &HttpClient::progress, this, std::placeholders::_1,
        std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)));
    request.perform();

    data = std::string(response.str());

    indicators::show_console_cursor(true);
    return curlpp::infos::ResponseCode::get(request) == 200;
  } catch (curlpp::RuntimeError& e) {
    indicators::show_console_cursor(true);
    std::cout << e.what() << std::endl;
  } catch (curlpp::LogicError& e) {
    indicators::show_console_cursor(true);
    std::cout << e.what() << std::endl;
  }
  return false;
}

bool HttpClient::download_file(std::string url, std::string path) {
  try {
    curlpp::Cleanup myCleanup;
    curlpp::Easy request;
    std::fstream myfile;
    myfile.open(
        path, std::ios::in | std::ios::out | std::ios::binary | std::ios::app);

    indicators::show_console_cursor(false);

    request.setOpt(curlpp::options::Url(url));
    request.setOpt(curlpp::options::WriteStream(&myfile));
    request.setOpt(curlpp::options::Verbose(false));
    request.setOpt(curlpp::options::NoProgress(0));
    request.setOpt(curlpp::options::ProgressFunction(std::bind(
        &HttpClient::progress, this, std::placeholders::_1,
        std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)));
    request.perform();
    myfile.close();
    indicators::show_console_cursor(true);
    return curlpp::infos::ResponseCode::get(request) == 200;
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
  if (percent < 0 || percent > 100) return 0;
  if (progressBar->current() == percent) return 0;
  progressBar->set_progress((int)percent);
  return 0;
}