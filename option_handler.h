/**********************************************************
 *
 * @project: OptionHandler
 * @author:  Ryan Gonzalez
 * @date:    February 11
 * @file:    option_handler.h
 *
 * Makes option handling for C++ programs easy.
 *
 **********************************************************/

#ifndef OPTION_HANDLER_H
#define OPTION_HANDLER_H

// Dependencies
#include <string>
#include <vector> 
#include <unordered_map>
#include <iostream>

namespace OptionHandler {

  enum class ArgumentType { NONE, REQUIRED, OPTIONAL };

  class Handler {
  private:  

    struct Option {

      char short_name;
      std::string long_name;
      ArgumentType type;
      bool multiple;

      Option( char         _short_name,
              std::string  _long_name,
              ArgumentType _type,
              bool         _multiple) :
              short_name(_short_name),
              long_name(_long_name),
              type(_type),
              multiple(_multiple) {};
    };

    // Properties
    std::vector<Option> declared_options;
    std::vector<std::string> input;
    std::unordered_map<std::string, std::vector<std::string>> parsed_input;

    // Private Methods
    void update(Option option);

  public:
    Handler(int argc, char** argv) : 
            input(std::vector<std::string>(argv + 1, argv + argc))
            {};

    // Public Methods
    Handler& add_option(char short_name, 
                    std::string long_name,
                    ArgumentType type,
                    bool multiple);

    // bool get_option(char short_name);
    bool get_option(std::string long_name);

    // std::string get_argument(char short_name);
    std::string get_argument(std::string long_name);
    std::vector<std::string> get_arguments(std::string long_name);

    bool is_short(std::string s) { 
      return ((s.at(0) == '-') && (s.at(1) != '-'));
    };
    bool is_long(std::string s)  {
      return ((s.at(0) == '-') && (s.at(1) == '-'));
    };  
  };


  inline Handler& Handler::add_option(char short_name, 
                                      std::string long_name,
                                      ArgumentType type,
                                      bool multiple) {

    // Add to declared options
    declared_options.push_back(Option(short_name, long_name, type, multiple));
    // Re-assess input
    update(declared_options.back());
    // Chain adding options 
    return *this;
  }

  // TODO: make short name getting easier
  // inline bool get_option(char short_name) {}
  inline bool Handler::get_option(std::string name) {
    return (parsed_input.find(name) != parsed_input.end());
  }

  inline std::string Handler::get_argument(std::string name) {
    if (parsed_input.find(name) == parsed_input.end())
      return "";
    else
      return parsed_input.at(name).empty() ? "" : parsed_input.at(name).front();
  }

  inline std::vector<std::string> Handler::get_arguments(std::string name) {
    if (parsed_input.find(name) == parsed_input.end())
      return std::vector<std::string>();
    else
      return parsed_input.at(name);
  }

  inline void Handler::update(Option option) {

    for (auto str = input.begin(); str != input.end(); ++str) {

      if ((*str).size() <= 1)
        continue;
      if ((*str).at(1) == option.short_name || (*str).substr(2) == option.long_name) {

        // Create empty vector if type = none
        if (option.type == ArgumentType::NONE) {
          // Only if it doesn't already exist in hash
          if (parsed_input.find(option.long_name) == parsed_input.end()) {
            // Insert empty vector
            parsed_input.insert(
              std::make_pair(option.long_name, std::vector<std::string>())
            );
          }
        }

        // Check if value exists, 
        // if ((option.type == ArgumentType::REQUIRED) && ((str+1) != input.end())) {
        //   // Exit if required but not present
        //   // TODO: more intuitive error handling
        //   if (is_long(*(str+1)) || is_short(*(str+1))) exit(1);

        //   if (parsed_input.find(option.long_name) == parsed_input.end()) {
        //     // Insert vector with value
        //     parsed_input.insert(
        //       std::make_pair(option.long_name, std::vector<std::string>(1, *(str+1)))
        //     );
        //   } else {
        //     parsed_input.at(option.long_name).push_back(*(str+1));
        //   }
        // }

        if (option.type == ArgumentType::OPTIONAL || option.type == ArgumentType::REQUIRED) {
          // If no value exists, insert empty vector
          if (((str+1) != input.end()) && (is_long(*(str+1)) || is_short(*(str+1)))) {
            if (parsed_input.find(option.long_name) == parsed_input.end()) {
              // Insert vector with value
              parsed_input.insert(
                std::make_pair(option.long_name, std::vector<std::string>())
              );
            }
          } else if ((str+1) != input.end()){
            if (parsed_input.find(option.long_name) == parsed_input.end()) {
              // Insert vector with value
              parsed_input.insert(
                std::make_pair(option.long_name, std::vector<std::string>(1, *(str+1)))
              );
            } else {
              parsed_input.at(option.long_name).push_back(*(str+1));
            }
          } else {
            if (parsed_input.find(option.long_name) == parsed_input.end()) {
              // Insert vector with value
              parsed_input.insert(
                std::make_pair(option.long_name, std::vector<std::string>())
              );
            }
          }
        }
      } 
    } // Handler::update()
  }
}

#endif
