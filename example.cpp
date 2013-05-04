#include <string>
#include <vector>
#include <iostream>
#include "option_handler.h"

void add_options(OptionHandler::Handler & h) {

  try {
    h.add_option('e', "exists", OptionHandler::NONE, false); }
  catch (const std::exception & e) {
    std::cerr << e.what() << std::endl; }

  try {
    h.add_option('h', "help",   OptionHandler::NONE, false); }
  catch (const std::exception & e) {
    std::cerr << e.what() << std::endl; }

  // Add some required options
  try {
    h.add_option('m', "movie",  OptionHandler::REQUIRED, false); }
  catch (const std::exception & e) {
    std::cerr << e.what() << std::endl; }

  try {
    h.add_option('f', "films",  OptionHandler::REQUIRED, true); }
  catch (const std::exception & e) {
    std::cerr << e.what() << std::endl; }

}

int main(int argc, char *argv[])
{

  OptionHandler::Handler h = OptionHandler::Handler(argc, argv);

  // None or required options should be used within a try/catch block
  add_options(h);

  // Add some optional options
  h.add_option('s', "song",   OptionHandler::OPTIONAL, false);
  h.add_option('a', "albums", OptionHandler::OPTIONAL, true);

  // get_option returns whether an option was set
  bool exists = h.get_option("exists"), 
       help   = h.get_option("help");

  // get_argument returns a string passed to an option
  std::string song  = h.get_argument("song"),
              movie = h.get_argument("movie");

  // get_arguments returns a vector of arguments (strings) passed to an option
  std::vector<std::string> albums = h.get_arguments("albums"),
                           films  = h.get_arguments("films");
 
  // Check if a exists was set
  if (exists)
    std::cout << "'exists' was set!" << std::endl;
  else
    std::cout << "'exists' was not set." << std::endl;
  // Check if help was set
  if (help)
    std::cout << "'help' was set!" << std::endl;
  else
    std::cout << "'help' was not set." << std::endl;

  // Print out arguments passed to song and movie
  std::cout << "Song:" << std::endl;
  std::cout << "  " << song << std::endl;
  std::cout << "Movie:" << std::endl;
  std::cout << "  " << movie << std::endl;

  // Print out passed albums arguments
  std::cout << "Albums:" << std::endl;
  for (unsigned int i = 0; i < albums.size(); ++i)
    std::cout << "  " << albums.at(i) << std::endl;
  
  // Print out passed films arguments
  std::cout << "Films:" << std::endl;
  for (unsigned int f = 0; f < films.size(); ++f)
    std::cout << "  " << films.at(f) << std::endl;

  return 0;
}
