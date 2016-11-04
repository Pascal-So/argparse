#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include "argparse.h"

void replaceAll( string &s, const string &search, const string &replace ) {
    for( size_t pos = 0; ; pos += replace.length() ) {
        // Locate the substring to replace
        pos = s.find( search, pos );
        if( pos == string::npos ) break;
        // Replace by erasing and inserting
        s.erase( pos, search.length() );
        s.insert( pos, replace );
    }
}

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

std::string concat_arguments(int argc, char *argv[]){
    std::string arguments = "";
    for(int i = 1; i < argc; ++i){
	std::string arg = argv[i];
	replaceAll(arg, " ", "\ ");
	arguments += arg + " ";
    }
    
    // remove the space at the end
    int len = arguments.length() -1;  
    return arguments.substr(0,len);
}


std::unordered_map<int, std::string> argparse (
					       std::vector<option> options,
					       int argc,
					       char *argv[]
					       )
{
    
    std::string arguments = concat_arguments(argc, argv);
    
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


