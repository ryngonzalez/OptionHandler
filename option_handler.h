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

/**********************************************************
 *
 * @class: OptionHandler
 * @method: handle()
 * @description: Parses the options struct, sets variables.
 *
 **********************************************************/

void OptionHandler::handle() {
  opterr = 0;
  for (int i = 0; i < num_opts; ++i) {
    short_options += options[i].val;
    if (options[i].has_arg)
      short_options += ':';
  }
}


/**********************************************************
 *
 * @class: OptionHandler
 * @method: get_option(char option)
 * @description: Returns whether a flag was passed in or not.
 *
 **********************************************************/


bool OptionHandler::get_option(char option) {
  int index = 0;
  int iarg = 0;

  while(iarg != -1) {
    iarg = getopt_long(num_args, args, short_options.c_str(), options, &index);
    if(iarg == option) {
      optind = 1;
      return true;
    }
  }

  optind = 1;

  return false;
}

/**********************************************************
 *
 * @class: OptionHandler
 * @method: get_argument(char option)
 * @description: Returns the argument provided for a
 * particular option. 
 *
 **********************************************************/


std::string OptionHandler::get_argument(char option) {
  int index = 0;
  int iarg = 0;

  while(iarg != -1) {
    iarg = getopt_long(num_args, args, short_options.c_str(), options, &index);
    if(iarg == option) {
      optind = 1;
      std::string s = optarg;
      return s;
    }
  }

  optind = 1;

  return "";
}

OptionHandler::~OptionHandler() {}


#endif
