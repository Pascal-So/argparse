#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include "argparse.h"

option get_option_by_shortname(std::vector<option> & options, std::string shortname){
    for(auto & o:options){
	if(o.shortname == shortname){
	    return o;
	}
    }
    
    return option {-1, "", "", false};
}

option get_option_by_longname(std::vector<option> & options, std::string longname){
    for(auto & o:options){
	if(o.longname == longname){
	    return o;
	}
    }

    return option {-1, "", "", false};
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

    // result will be stored in here
    std::unordered_map<int, std::string> result;

    // return this in case of an error
    std::unordered_map<int, std::string> error;
    error[-1] = "ERROR";
    
    std::vector<std::string> arguments = convert_arguments(argc, argv);

    // ids of unnamed options available
    std::vector<int> unnamed_options = find_unnamed_options(options);

    // this index will iterate over the unnamed_options. If
    // the arguments contain too many unnamed options, an error
    // is printed out to stderr.
    int current_unnamed_option;

    // what kind of option type are we currently reading
    // while looping through the arguments string?
    enum state {noArg, shortArg, longArg};
    
    // the current state of the parser: this will start at noArg,
    // then change to shortArg or longArg if one or two dashes are
    // found, and back to noArg after that.
    state current_state = noArg;

    // bash has already split up the arguments accordingly,
    // so we don't need to worry about whitespace.
    for(int i = 0; i < arguments.size(); ++i){
	
	int argstrlen = arguments[i].length();
	
	//std::cout<<argument<<"\n";
	
	// pos is the current position in the argument string.
	for(int pos = 0; pos<argstrlen; ++pos){
	    switch (current_state){
	    case noArg:{
		if(pos < argstrlen-1 && arguments[i][pos] == '-'){
		    // starts with a dash. Either beginning of short
		    // or long arg.
		    if(pos < argstrlen-2 && arguments[i][pos+1] == '-'){
			current_state = longArg;
		    }else{
			current_state = shortArg;
		    }
		}else{
		    // encountering an unnamed argument, read
		    // until the end of the current string.
		    std::string unnamed_arg = arguments[i].substr(pos);
		    pos = argstrlen;
		    
		    if(current_unnamed_option >= unnamed_options.size()){
			// too many unnamed options, print an error message
			// and abort.
			std::cerr<<"ERROR: too many unnamed options.\n";
			return error;
		    }
		    int id = unnamed_options[current_unnamed_option++];

		    result[id] = unnamed_arg;
		}
		break;
	    }
	    case shortArg:{
		// weird c++ hack because we can't cast char to
		// string. Why is this so hard?
		std::string shortname = "";
		shortname += arguments[i][pos];
		
		option o = get_option_by_shortname(options, shortname);

		if(o.id == -1){
		    // unknown short option, print error
		    std::cerr<<"ERROR: unknown short option: -"<<shortname<<"\n";
		    return error;
		}

		std::string sub_argument = "";
		
		if(o.has_sub_argument){

		    if(pos == argstrlen-1){
			// argument is in next argument block
			++i;
			if(i == arguments.size()){
			    // reached end of argument blocks, print error
			    std::cerr<<"ERROR: missing sub-argument for -"<<shortname<<"\n";
			    return error;
			}
			
			// move pointer to the end of new argument block
			pos = arguments[i].length();
			
			sub_argument = arguments[i];

			// test if this really is a sub-argument or a new argument
			// instruction:
			if(sub_argument[0] == '-'){
			    // no sub-argument give, print error
			    std::cerr<<"ERROR: missing sub-argument for -"<<shortname<<"\n";
			    return error;
			}
			
		    }else{
			// read until the end of current string
			sub_argument = arguments[i].substr(pos);
		    }   
		}

		result[o.id] = sub_argument;
		
		current_state = noArg;
		break;
	    }
	    case longArg:{
		std::string longname = arguments[i].substr(pos);

		option o = get_option_by_longname(options, longname);

		if(o.id == -1){
		    // unknown short option, print error
		    std::cerr<<"ERROR: unknown long option: --"<<longname<<"\n";
		    return error;
		}
		
		// long arg always fills the argument block, because there has to be
		// a space after the argument name.
		++i;
		if(i == arguments.size()){
		    // reached end of argument blocks, print error
		    std::cerr<<"ERROR: missing sub-argument for --"<<longname<<"\n";
		    return error;
		}
		
		// move pointer to the end of new argument block
		pos = arguments[i].length();

		std::string sub_argument = arguments[i];

		// test if this really is a sub-argument or a new argument
		// instruction:
		if(sub_argument[0] == '-'){
		    // no sub-argument give, print error
		    std::cerr<<"ERROR: missing sub-argument for --"<<longname<<"\n";
		    return error;
		}

		result[o.id] = sub_argument;

		current_state = noArg;
		break;
	    }
	    }
	}
    }
    
    
    
    return result;
}


