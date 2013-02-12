#include <string>
#include <iostream>
#include "option_handler.h"

using namespace std;

int main(int argc, char *argv[])
{
  // Define the options you want to handle.
  const struct option options[5] = {
    {"output",  required_argument,  0, 'o'},
    {"stack",   no_argument,        0, 's'},
    {"queue",   no_argument,        0, 'q'},
    {"help",    no_argument,        0, 'h'},
    {0, 0, 0, 0}
  };

  // Create the option handler
  OptionHandler h = OptionHandler(argc, argv, options, 5);

  // Get a bool indicating whether a flag was set
  bool s = h.get_option('s'),
       q = h.get_option('q');

 // Get the argument passed to the long or short flag
  string o = h.get_argument('o');

  // Get your return values
  cout << s << endl;
  cout << q << endl;
  cout << o << endl;

  return 0;
}
