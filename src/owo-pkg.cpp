#include "owo-pkg.h"

#include <string>
#include "cli.h"

int main(int argc, char* argv[]) {

  setup_cli(argc, argv);

  /*  argparse::ArgumentParser program("owo", "0.1", );
    program.add_description(
        "owo is a private package manager for installing packages on multiple "
        "platforms and systems.");

    // program.add_argument("command");

    program.add_argument("install")
        .help("install packages");

    program.add_argument("update")
        .help("update packages")
        .default_value(false)
        .implicit_value(true);

    program.add_argument("remove")
        .help("remove packages")
        .default_value(false)
        .implicit_value(true);

    program.add_argument("install").help("install packages");

    program.add_argument("update")
        .help("update packages and repositories cache");

    program.add_argument("remove").help("remove packages");

    program.add_argument("packages").remaining();

    program.add_argument("--verbose")
        .help("increase output verbosity")
        .default_value(false)
        .implicit_value(true);

    try {
      program.parse_args(argc, argv);
    } catch (const std::runtime_error& err) {
      std::cout << err.what() << std::endl;
      std::cout << program;
      exit(0);
    }

    std::cout << "Has install: " << program.is_used("install");
    if (program.is_used("install")) {
      //auto data = program.get("install");
      std::cout << " -> ";
    }
    std::cout << "\n";

    auto command = program.get("command");

    if (command == "install") {
      try {
        auto packages = program.get<std::vector<std::string>>("packages");
        std::cout << "install " << packages.size() << " packages" << std::endl;
        for (auto& package : packages) std::cout << package << std::endl;
      } catch (std::logic_error& e) {
        std::cout << "No package provided" << std::endl;
      }
    } else if (command == "update") {
      try {
        auto packages = program.get<std::vector<std::string>>("packages");
        std::cout << "update " << packages.size() << " packages" << std::endl;
        for (auto& package : packages) std::cout << package << std::endl;
      } catch (std::logic_error& e) {
        std::cout << "No package provided" << std::endl;
      }
    } else if (command == "remove") {
      try {
        auto packages = program.get<std::vector<std::string>>("packages");
        std::cout << "remove " << packages.size() << " packages" << std::endl;
        for (auto& package : packages) std::cout << package << std::endl;
      } catch (std::logic_error& e) {
        std::cout << "No package provided" << std::endl;
      }
    } else {
      std::cout << program << std::endl;
    }*/
}