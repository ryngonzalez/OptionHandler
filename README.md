# OptionHandler 0.2
Make handling command line options in C++ easy with a sane, simple API. A replacement for [getopt_long](http://www.gnu.org/software/libc/manual/html_node/Getopt.html#Getopt).

## Useage
To use with your code, simply include `option_handler.h` in your `.cpp`, `.hpp`, or `.h` file.

### Command Line Usage

On the command line you can allow your program to take in long or short options.

    ./myprogram --mode FASTMODE --stocks GOOG AAPL AMZN --statistics

This is equivalent:

    ./myprogram -m FASTMODE -s GOOG AAPL AMZN -t

### Developer Usage

#### Instantiation

Instantiate an option handler by passing in the command line input (`argv` and `argc`):

    OptionHandler::Handler h = OptionHandler::Handler(argc, argv);

##### Adding Options

Add options with `add_option`:

    // Follows h.add_option(short_name, long_name, arg_type, multiple);
    // For example: 
    h.add_option('m', "mode", OptionHandler::REQUIRED, false);

And options has these arguments:

1. `short_name` is a `char`
2. `long_name` is a `std::string`
3. `arg_type` is one of 
  * `OptionHandler::NONE`
      * If an option is NONE, and an argument is passed to it, an exception is thrown
      * All NONE options should be wrapped in a try/catch block 
  * `OptionHandler::REQUIRED`
      * If an option is REQUIRED, and no argument is passed to it, an exception is thrown
      * All REQUIRED options should be wrapped in a try/catch block 
  * `OptionHandler::OPTIONAL`
4. `multiple` is a bool indicating whether an argument can take multiple arguments
  * if `multiple` is set to `false` the last argument passed to the option is set as it's only argument
  * if `multiple` is set to `true` all arguments passed to the option are saved in a `vector<string>`

#### Accessing Options

All accessors are called by passing in the desired option's `long_name`.

##### Checking if an option was set

To check whether an option has been used, call `get_option`:

    // get_option returns whether an option was set
    bool exists = h.get_option("exists"), 
         help   = h.get_option("help");

##### Get an argument passed to an option

To get the last argument passed to an option, call `get_argument`:

    // get_argument returns a string passed to an option
    std::string song  = h.get_argument("song"),
                movie = h.get_argument("movie");

##### Get all arguments passed to an option

To get a `vector<string>` of all arguments passed to an option, call `get_arguments`:

    // get_arguments returns a vector of arguments (strings) passed to an option
    std::vector<std::string> albums = h.get_arguments("albums"),
                             films  = h.get_arguments("films");

## License
Copyright (&copy;) 2012 Ryan Gonzalez <ryan@ionizedmedia.com> &amp; Haoran Ning <hning@umich.edu>

Permission is hereby granted, free of charge, to any person obtaining a copy of 
this software and associated documentation files (the "Software"), to deal in 
the Software without restriction, including without limitation the rights to 
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies 
of the Software, and to permit persons to whom the Software is furnished to do 
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all 
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
SOFTWARE.
