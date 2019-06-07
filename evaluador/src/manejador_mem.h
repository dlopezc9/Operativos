#pragma once
#include <string.h>

using namespace std;

class Manejador_Mem {
    public:
        int crear_mem(int i, int ie, int oe, string n, int b, int d, int s, int q);
        char * abrir_memoria(string n);
        registrosalida retirar_reg(int bandeja, string n);
        int recorrer_mem(string nombre);

        int recorrerQ(string nombre);        
        int crear_memQ(string n);
        char * abrir_memoriaQ(string n);  
};