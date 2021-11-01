#include "cli.h"

#include <iostream>

#include "commands/install.h"
#include "commands/remove.h"
#include "commands/update.h"

void setup_cli(int argc, char* argv[]) {
  enum class mode { install, update, remove, help };

  mode selected = mode::help;

  std::vector<std::string> packages;

  auto installMode = (clipp::command("install").set(selected, mode::install),
                      clipp::values("packages", packages));

  auto updateMode = (clipp::command("update").set(selected, mode::update),
                     clipp::values("packages", packages));

  auto removeMode = (clipp::command("remove").set(selected, mode::remove),
                     clipp::values("packages", packages));

  auto cli = (installMode | updateMode | removeMode |
              clipp::command("help").set(selected, mode::help));

  if (parse(argc, argv, cli)) {
    switch (selected) {
      case mode::install:
        cmd::install();
        break;
      case mode::update:
        cmd::update();
        break;
      case mode::remove:
        cmd::remove();
        break;
      case mode::help:
        print_usage();
        break;
    }
  } else {
    print_usage();
  }
}

void print_usage() {
  std::cout << "owo-pkg v1.0.0\n";
  std::cout << "Usage: owo [options] command\n\n";
  std::cout
      << "owo-pkg is a private package manager for installing packages.\n\n";
  std::cout << "Commands:\n";
  std::cout << "  install <packages>\n";
  std::cout << "  update <packages>\n";
  std::cout << "  remove <packages>";
  std::cout << std::endl;
}