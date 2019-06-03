#include <iostream>
#include <cstdlib>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <sstream>

using namespace std;

string * parser(string line)
{
  int i = 0;
  static string arr[3];
  stringstream ssin(line);

  while(ssin.good() && i < 3)
  {
    ssin >> arr[i];
    ++i;
  }

  return arr;
}

int main(int argc, char* argv[]){

  string memory_space(argv[2]);
  bool listen = true;
  string command;
  int valor;
  
  while(listen)
  {
    cout << ">";
    getline(cin, command);
    string *second_input = parser(command);
    
    if(second_input[0] == "list"){
      if(second_input[1] == "processing"){

      } else if(second_input[1] == "waiting"){

      } else if(second_input[1] == "reported"){

      } else if(second_input[1] == "reactive"){

      } else if(second_input[1] == "all"){

      }
    } else if(second_input[0] == "update"){
      string tipo = second_input[1];
      valor = atoi(second_input[2].c_str());
      
      listen = false;
      
    }


  }

  return 0;
}
