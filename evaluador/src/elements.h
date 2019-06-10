#pragma once

#include <string>

using namespace std;

class Elements {
    public:
    int generar_id();
    int generar_resultado();
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
   int contador;
};

struct headerQ {
  int q;
  int i;
  int b;
  int d;
  int s;
};

struct registroentrada {
  int bandeja;
  int id;
  char tipo;
  int cantidad;
  int time;
};

// externo -> nombrado
// interno -> anonimo
struct registrosalida{
  int id;
  int bandeja;
  char tipo;
  int cantidad;
  int time;
  char resultado;
};