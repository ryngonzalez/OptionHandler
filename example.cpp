#include <string>
#include <iostream>
#include "option_handler.h"

int main(int argc, char *argv[])
{

  OptionHandler::Handler h = OptionHandler::Handler(argc, argv);

  // Setup options
  h.add_option('m', "mode", OptionHandler::ArgumentType::REQUIRED, false);
  h.add_option('h', "help", OptionHandler::ArgumentType::NONE,     false);

  // Check if options were passed to the program
  bool help = h.get_option("help");
  bool mode_set = h.get_option("mode");
  // Get the argument passed to a particular option
  std::string mode = h.get_argument("mode");

  // Check if 'help' option was set
  if (help)
    std::cout << "The options for this program are..." << std::endl;

  // Make sure 'mode' option is set and that an argument was provided to it.
  if (!mode_set || mode == "") {
    std::cerr << "Mode must be set.\n";
    exit(1);
  }

  // Check the values
  std::cout << help     << std::endl;
  std::cout << mode     << std::endl;
  std::cout << mode_set << std::endl;

  return 0;
}
