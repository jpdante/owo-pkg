#include "install.h"

#include <iostream>
#include "../http.h"

namespace cmd {

void install() { 
  std::cout << "Install" << std::endl;
  HttpClient client;
  client.downloadFile("http://ovh.net/files/10Mio.dat", "../tmp/data.bin");
}

}  // namespace cmd