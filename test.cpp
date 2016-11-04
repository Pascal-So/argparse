#include "argparse.h"
#include <iostream>

using namespace std;

int main(int argc, char * argv[]){
  vector<option> v;

  v.push_back({0, "", "", false});
  v.push_back({1, "i", "include", true});
  v.push_back({2, "f", "", false});
  v.push_back({3, "r", "", false});
  v.push_back({4, "o", "outfile", true});
  
  auto result = argparse(v, argc, argv);

  for(auto kv:result){
      cout<<kv.first << " - " << kv.second<<"\n";
  }
}
