#include <iostream>
#include <cstdlib>
#include <string.h>
#include <stdio.h>
#include <iterator>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[])
{

  int i = 5;
  int ie = 6, q = 6;
  int oe = 10;
  int d = 100, b = 100, s = 100;
  string n = "evaluator";

  
  if (argc == 1) {
    cout << "Insuficientes argumentos, porfavor intentar de nuevo";
    return 1;
  }

  if (strcmp(argv[1],"init")){
    cout << "Falta comando init" << endl;
    return 1;
  }

  string arguments[] = { "-i", "-ie", "-oe", "-n", "-d", "-b", "-s", "-q" };

  for (int x = 2; x < argc; ++x) {

    //    cout << "ARGUMENTO ACTUAL: " << argv[x] << endl;
    //    cout << "ESTA EN LA POSICION: " << x << endl;
    
    string t_argument(argv[x]);
    bool exists = find(begin(arguments), end(arguments), t_argument) != end(arguments);
    
    if(!exists){
      cout << "Argumento invalido" << endl;
      cout << "El argumento invalido es: " << argv[x] << endl;
      return 1;
    }
    
    if(!strcmp(argv[x],"-i")) {
	    i = atoi(argv[x + 1]);
	    ++x;
	    
	    if(i == 0){
	        cout << "Valor no autorizado para i" << endl;
	        return 1;
	    }
    }

    if(!strcmp(argv[x],"-ie")) {
	    ie = atoi(argv[x + 1]);
	    ++x;
	    
	    if(ie == 0){
	        cout << "Valor no autorizado para ie" << endl;
	        return 1;
	    }
    }

    if(!strcmp(argv[x],"-oe")) {
	    oe = atoi(argv[x + 1]);
	    ++x;
	    
	    if(oe == 0){
	        cout << "Valor no autorizado para oe" << endl;
	        return 1;
	    }
    }

    if(!strcmp(argv[x],"-n")) {
	    string temp(argv[x + 1]);
	    n = temp;
	    ++x;
    }

    if(!strcmp(argv[x],"-d")) {
	    d = atoi(argv[x + 1]);
	    ++x;
	    
	    if(d == 0 || d > 100 ){
	        cout << "Valor no autorizado para d" << endl;
	        return 1;
	    }
    }    

    if(!strcmp(argv[x],"-b")) {
	    b = atoi(argv[x + 1]);
	    ++x;
	    
	    if(b == 0 || b > 100 ){
	      cout << "Valor no autorizado para b" << endl;
	      return 1;
	    }
    }

    if(!strcmp(argv[x],"-s")) {
	    s = atoi(argv[x + 1]);
	    ++x;
	    
	    if(s == 0 || s > 100 ){
	        cout << "Valor no autorizado para s" << endl;
	        return 1;
	    }
    }
    
    if(!strcmp(argv[x],"-q")) {
	    q = atoi(argv[x + 1]);
	    ++x;
	    
	    if(q == 0 || q > 100 ){
	        cout << "Valor no autorizado para q" << endl;
	        return 1;
	    }
    }
  }
  
  cout <<  "Valor de i: " << i << endl;
  cout <<  "Valor de ie: " << ie << endl;
  cout <<  "Valor de oe: " << oe << endl;
  cout <<  "Valor de n: " << n << endl;
  cout <<  "Valor de d: " << d << endl;
  cout <<  "Valor de b: " << b << endl;
  cout <<  "Valor de s: " << s << endl;
  cout <<  "Valor de q: " << q << endl;

  return 0;
}
