#include "install.h"

#include <iostream>
#include "../http.h"

namespace cmd {

void install() { 
  std::cout << "Install" << std::endl;
  download();
}

}  // namespace cmd