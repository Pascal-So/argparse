# argparse
Parsing command line arguments in C++

Note that my naming conventions differ a bit from the standart:
* What POSIX® calls *"operands"*, are denoted as *"unnamed arguments"* in my code and comments.
* Arguments that follow after options are called *"sub-arguments"* in my code, instead of *"option arguments"*.

## Limitations and advantages
To get it out of the way upfront, this library has some limitations:
* Doesn't allow the same argument to be passed multiple times.
* Doesn't allow the character `-` as a standalone argument.

But also some advantages:
* Lighter than boost or other alternative
* The above limitations allow for a much easier syntax when using the library
* It's fast

## Usage

First, include the library:
```c++
#include "path/to/argparse.hpp"
```

The library introduces a struct called `option`, which lets the user describe an expected command line option. It contains the following fields:
* `id` - used to give the option an unique identifier by which it can be retrieved after parsing.
* `shortname` - the short option name that will be used after a single dash.
* `longname` - the long option name that will be used after two dashes.
* `has_sub_argument` - Does the option expect a sub-argument afterwards?

We first a vector of these options and fill it with the options we allow the user to pass to the program on the command line:

```c++
vector<option> options;

options.push_back({0, "i", "include", true});
options.push_back({1, "f", "force", false});
options.push_back({2, "r", "", false});
```
This will allow the user to write commands like the following:

```bash
prog -i fileA --force -r
prog -rfi fileA
```
These two lines are equivalent.

To tell the parser to look for an unnamed argument (in POSIX® terms: operand), we have to create an `option` with the `shortname` and `longname` both set to "":

```c++
options.push_back({3, "", "", true}); // note that the field has_sub_argument is ignored in this case
```

This will allow for commands like the following:
```bash
prog -i fileA output.txt
prog output.txt -i fileA
```
And again, the above two lines are equivalent. Note that the order of arguments only ever plays a role for multiple unnamed options, otherwise all allowed arrangements are equivalent.

After setting up the options, we can now run the parser with the following command:
```c++
unordered_map<int, string> result = argparse(options, argc, argv);
```

The `unordered_map result` will contain the keys of all the options that occurred in the arguments. If the option requires a sub-argument, the value assiciated to the key will contain the sub-argument. To test this out, we could print the resulting `unordered_map` like this:
```c++
for(auto r:result){
  cout << r.first << "-" << r.second << "\n";
}
```

## Compiling

To compile anything with argparse, we first have to run the makefile in the argparse directory:
```bash
make -C path/to/argparse	
```

Then, we can compile the program. Assuming that the code is saved in `prog.cpp` and that the file `argparse.o` is in the subdirectory `argparse/`:
```bash
g++ -std=c++11 -o prog prog.cpp argparse/argparse.o
```

After that, we can run the program like this:
```bash
$ ./prog -i fileA output.txt
0 - fileA
3 - output
$ ./prog -ri fileA
0 - fileA
2 - 
```

## Error handling
In case of an error, `argparse` prints an error message to stderr and returns an unordered_map with just a single key-value pair: `{-1, "ERROR"}`.