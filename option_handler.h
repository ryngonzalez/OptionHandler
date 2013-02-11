#ifndef OPTION_HANDLER_H
#define OPTION_HANDLER_H
/**********************************************************
 *
 * @project: OptionHandler
 * @author:  Ryan Gonzalez
 * @date:    February 11
 * @file:    option_handler.h
 *
 * Defines the input libraries for taking in and parsing
 * maps and coordinate lists. 
 *
 **********************************************************/

// Dependencies
#include <getopt.h>
#include <string>

/**********************************************************
 *
 * @class: OptionHandler
 * @description: Parses argv and determines whether flags
 * are set.
 *
 **********************************************************/

class OptionHandler {
private:  
  const struct option* options;
  int num_args;
  int num_opts;
  char** args;
  std::string short_options;
  void handle();
public:
  OptionHandler(int argc, char** argv, const struct option *user_options, int num) : 
                options(user_options),
                num_args(argc),
                num_opts(num),
                args(argv),
                short_options("") {
                  handle();
                };

  bool get_option(char option);
  std::string get_argument(char option);
  ~OptionHandler();

};

#endif
