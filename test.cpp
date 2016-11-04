#include "argparse.h"
#include <iostream>

using namespace std;

int main(int argc, char * argv[]){
  vector<option> v;
  argparse(v, argc, argv);
}
