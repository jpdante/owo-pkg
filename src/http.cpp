#include "http.h"

#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/cURLpp.hpp>

void download() {
  try {
    curlpp::Cleanup myCleanup;
    std::cout << curlpp::options::Url("http://google.com");
  } catch (curlpp::RuntimeError &e) {
    std::cout << e.what() << std::endl;
  } catch (curlpp::LogicError &e) {
    std::cout << e.what() << std::endl;
  }
}