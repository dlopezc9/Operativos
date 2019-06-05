<<<<<<< HEAD
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <iostream>
#include <cstdlib>
#include <cerrno>
#include <cstring>
#include <unistd.h>
#include "elementos.h"

using namespace std;
int main(){return 1;}
=======
#include <iostream>
#include <cstdlib>
#include <string.h>
#include <stdio.h>

using namespace std;

int main(int argc, char* argv[])
{

  int i = 5;
  int ie, q = 6;
  int oe = 10;
  int d, b, s = 100;
  string n = "evaluator";

  if (argc == 1) {
    cout << "Insuficientes argumentos, porfavor intentar de nuevo";
    return 1;
  }

  for (int x = 0; x < argc; ++x){
    if(!strcmp(argv[x],"-i")) {
	    i = atoi(argv[x + 1]);
	
	    if(i == 0){
	        cout << "Valor no autorizado para i" << endl;
	        return 1;
	    }
	
	    cout << "La variable ";
	    cout << arg[x];
	    cout << " se le asigno el valor ";
	    cout << argv[x + 1] << endl;
    }

    if(!strcmp(argv[x],"-ie")) {
	    ie = atoi(argv[x + 1]);
	
	    if(ie == 0){
	        cout << "Valor no autorizado para ie" << endl;
	        return 1;
	    }
	
	    cout << "La variable ";
	    cout << arg[x];
	    cout << " se le asigno el valor ";
	    cout << argv[x + 1] << endl;
    }

    if(!strcmp(argv[x],"-oe")) {
	    oe = atoi(argv[x + 1]);
	
	    if(oe == 0){
	        cout << "Valor no autorizado para oe" << endl;
	        return 1;
	    }
	
	    cout << "La variable ";
	    cout << arg[x];
	    cout << " se le asigno el valor ";
	    cout << argv[x + 1] << endl;
    }

    if(!strcmp(argv[x],"-n")) {
	    n(argv[x + 1]);
	
	    if(n == 0){
	        cout << "Valor no autorizado para n" << endl;
	        return 1;
	    }
	
	    cout << "La variable ";
	    cout << arg[x];
	    cout << " se le asigno el valor ";
	    cout << argv[x + 1] << endl;
    }

    if(!strcmp(argv[x],"-d")) {
	    d = atoi(argv[x + 1]);
	
	    if(d == 0 || d > 100 ){
	        cout << "Valor no autorizado para d" << endl;
	        return 1;
	    }
	
	    cout << "La variable ";
	    cout << arg[x];
	    cout << " se le asigno el valor ";
	    cout << argv[x + 1] << endl;
    }    

    if(!strcmp(argv[x],"-b")) {
	    b = atoi(argv[x + 1]);
	
	    if(b == 0 || b > 100 ){
	    cout << "Valor no autorizado para b" << endl;
	    return 1;
	}
	
	    cout << "La variable ";
	    cout << arg[x];
	    cout << " se le asigno el valor ";
	    cout << argv[x + 1] << endl;
    }

    if(!strcmp(argv[x],"-s")) {
	    s = atoi(argv[x + 1]);
	
	    if(s == 0 || s > 100 ){
	        cout << "Valor no autorizado para s" << endl;
	        return 1;
	}
	
	    cout << "La variable ";
	    cout << arg[x];
	    cout << " se le asigno el valor ";
	    cout << argv[x + 1] << endl;
    }
    
    if(!strcmp(argv[x],"-q")) {
	    q = atoi(argv[x + 1]);
	
	    if(q == 0 || q > 100 ){
	        cout << "Valor no autorizado para q" << endl;
	        return 1;
	}
	
	    cout << "La variable ";
	    cout << arg[x];
	    cout << " se le asigno el valor ";
	    cout << argv[x + 1] << endl;
    }       
  }


  return 0;
>>>>>>> master
}