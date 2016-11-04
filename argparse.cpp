#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include "argparse.h"

int get_id_by_shortname(std::vector<option> & options, std::string shortname){
    for(auto & o:options){
	if(o.shortname == shortname){
	    return o.id;
	}
    }
    return -1;
}

int get_id_by_longname(std::vector<option> & options, std::string longname){
    for(auto & o:options){
	if(o.longname == longname){
	    return o.id;
	}
    }
    return -1;
}


// find the ids of all the options for unnamed
// arguments. Keeps the order from the options
// vector.
std::vector<int> find_unnamed_options(std::vector<option> & options){
    std::vector<int> unnamed;
    for(auto & o:options){
	if(o.shortname == "" &&
	   o.longname == ""){
	    unnamed.push_back(o.id);
	}
    }
    return unnamed;
}


// convert the array of c strings to an std::vector
// of std::strings, ignoring the first element in
// the array.
std::vector<std::string> convert_arguments(int argc, char *argv[]){
    std::vector<std::string> arguments;
    for(int i = 1; i < argc; ++i){
	arguments.push_back(argv[i]);
    }
    
    return arguments;
}


std::unordered_map<int, std::string> argparse (
					       std::vector<option> options,
					       int argc,
					       char *argv[]
					       )
{
    
    std::vector<std::string> arguments = convert_arguments(argc, argv);
    
    std::vector<int> unnamed_options = find_unnamed_options(options);

    // what kind of option type are we currently reading
    // while looping through the arguments string?
    enum state {noArg, shortArg, longArg};
    
    // the current state of the parser: this will start at noArg,
    // then change to shortArg or longArg if one or two dashes are
    // found, and back to noArg after that.
    state current_state = noArg;
    
    // position in the arguments string.
    int pos = 0;

    int argstrlen = arguments.length();

    std::cout<<arguments<<"\n";

    

    // one iteration through this loop will always consume either
    // an entire argument with its sub-argument, the change from 
    // noArg mode to either shortArg or longArg mode, or some
    // whitespace.
    while (pos < argstrlen){
	while(pos<argstrlen)
	    switch (current_state){
	    case noArg:
		if(pos < argstrlen-1 && arguments[pos] == '-'){
		    if(pos < argstrlen-2 && arguments[pos+1] == '-'){
			current_state = longArg;
		    }else{
			current_state = shortArg;
		    }
		}else{
		    
		}
	    
		break;
	    case shortArg:
		break;
	    case longArg:
		break;
	    }
    }
    
    
    
    std::unordered_map<int, std::string> result;
    
    return result;
}


