#pragma once
#include <string.h>

using namespace std;

class Manejador_Mem {
    public:
        int crear_mem(int i, int ie, int oe, string n, int b, int d, int s, int q);
        char * abrir_memoria(string n);
        registrosalida retirar_reg(int bandeja, string n);
};