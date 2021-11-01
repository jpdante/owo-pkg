#pragma once

#include <iostream>

class Repository {
 public:
  Repository(std::string name, std::string url);

 public:
  std::string Name;
  std::string Url;
  std::string Path;
};

Repository* read_repository(std::string file);

bool save_repository(Repository* repository, std::string file);