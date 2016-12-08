#ifndef ARGPARSE_H_
#define ARGPARSE_H_

#include <unordered_map>
#include <string>
#include <vector>

/*

argparse - Tool to parse unix style arguments.

The function argparse is called with a vector of structs "option", in
which the expected options are described. A single element of type
"option" contains:

- The id, which serves as the internal representation of this option
  type. This code will also be used to identify the option type in the 
  return value.
 
- The name of the short option name (after a single dash, for example 
  "-l") without the dash. This has to be a single character, or if no 
  short name is given for this option then an empty string.

- The long name of the option (after two dashes, for example "--help")
  without the dashes, or if no long name is given for this option then 
  an empty string.

- A boolean telling the parser whether or not this option expects an 
  additional sub-argument, for example "-i in.txt". If the additional
  sub-argument has no spaces or special bash characters in it, it could
  also be written directly after the dash option, for example "-d,", 
  which would pass the string "," as the sub-argument for "-d".

To tell argparse to expect an unnamed argument (for example filename
in "cat filename"), an option can be passed along in the vector of
options with shortname and longname both set to the empty string "".
If there are multiple unnamed arguments, they will be assigned to the
ids in the order that the ids were passed inside the options vector.

The function argparse also expects the values of argc and *argv[], as
received by the main function.

argparse returns an unordered_map from int to string listing all the
options that were actually found in argv, where the int is the option
id and the string is either the empty string "" or the added 
sub-argument to this options.

argparse will print to stderr in case of an error.

Pascal Sommer, November 2016

 */


struct option{
  int id;
  std::string shortname;
  std::string longname;
  bool has_sub_argument;
};

std::unordered_map<int, std::string> argparse (
					       std::vector<option> options,
					       int argc,
					       char *argv[]
					       );

#endif // ARGPARSE_H_
