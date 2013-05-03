#include <string>
#include <iostream>
#include <vector>
#include "option_handler.h"

using namespace std;

int main(int argc, char *argv[])
{

  OptionHandler::Handler h = OptionHandler::Handler(argc, argv);

  // Setup options
  h.add_option('m', "mode", OptionHandler::ArgumentType::REQUIRED, true);
  h.add_option('h', "help", OptionHandler::ArgumentType::NONE,     false);

  cout << "Done" << endl;

  // Check if options were passed to the program
  bool help = h.get_option("help");
  bool mode_set = h.get_option("mode");
  // Get the argument passed to a particular option
  std::vector<std::string> mode = h.get_arguments("mode");

  cout << "Size of mode: " << mode.size() << endl;

  // Check if 'help' option was set
  if (help)
    std::cout << "The options for this program are..." << std::endl;

  // Check the values
  std::cout << help     << std::endl;
  for(auto i : mode)
  {
    std::cout << i << " ";
  }
  std::cout << std::endl;
  std::cout << mode_set << std::endl;

  return 0;
}
