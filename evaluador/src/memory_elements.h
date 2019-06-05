#pragma once

#include <string>

using namespace std;

class Memory_Elements {
    public:
    char* abrir_memoria(string n);
};

struct header {
   int i;
   int ie;
   int oe; 
   char n[30];
   int b;
   int d;
   int s;
   int q;
};


struct registroentrada {
  int bandeja;
  int id;
  char tipo[1];
  int cantidad;
};

// externo -> nombrado
// interno -> anonimo
struct registrosalida{
  int id;
  char tipo[1];
  int cantidad;
};