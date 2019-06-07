#pragma once

#include <string>

using namespace std;

class Elements {
    public:
    int generar_id();
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

struct headerQ {
  int q;
};

struct registroentrada {
  int bandeja;
  int id;
  char tipo;
  int cantidad;
};

// externo -> nombrado
// interno -> anonimo
struct registrosalida{
  int id;
  char tipo;
  int cantidad;
};