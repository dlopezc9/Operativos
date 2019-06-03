#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <cstdlib>

using namespace std;

string * parser(string line)
{
  int i = 0;
  static string arr[4];
  stringstream ssin(line);

  while (ssin.good() && i < 4)
  {
    ssin >> arr[i];
    ++i;
  }
  
  return arr;
}

int main(int argc, char* argv[]){
  
  string memory_name(argv[2]);

  if(!strcmp(argv[3], "-i"))
  {
    cout << "COmando era -i" << endl;
  } else if (!strcmp(argv[3], "-m")) {
    cout << "Comando era -m" << endl;
  }

  return 0;
}
