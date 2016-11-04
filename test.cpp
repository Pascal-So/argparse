#include "argparse.h"
#include <iostream>

using namespace std;

int main(int argc, char * argv[]){
  

  /*

    Use this to test argparse.

    Example: 
    
    ./test -ri fileA inputFile --outfile outputFile

    where -r and -i are short options, fileA is a sub-argument
    for -i, inputFile is an unnamed argument, --output is a 
    long option with the sub-argument outputFile.

    should print:
    0 - inputFile
    1 - fileA
    3 - 
    4 - outputFile

   */


    vector<option> options; // options vector
    
    options.push_back({0, "", "", true});           // unnamed option
    options.push_back({1, "i", "include", true});   // option with sub-argument
    options.push_back({2, "f", "", false});         // option -f
    options.push_back({3, "r", "", false});         // -r
    options.push_back({4, "o", "outfile", true});   // -o or --outfile, requiring sub-argument
    options.push_back({5, "e", "else", true});      // -o or --else, requiring sub-argument
    options.push_back({6, "", "", true});           // unnamed option
    
    auto result = argparse(options, argc, argv);

    if(result.find(-1) != result.end()){
      cout<<"The parser encountered an error. See stderr for details.\n";
      return 1;
    }
    
    for(auto kv:result){
	cout<<kv.first << " - " << kv.second<<"\n";
    }
}
