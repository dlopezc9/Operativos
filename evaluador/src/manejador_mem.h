#pragma once
#include <string.h>

using namespace std;

class Manejador_Mem {
    public:
        int crear_mem(int i, int ie, int oe, string n, int b, int d, int s, int q);
        char * abrir_memoria(string n);
        registrosalida retirar_reg(int bandeja, string n);
        int recorrer_mem(string n);

        int recorrerQ(string n);        
        int crear_memQ(string n);
        char * abrir_memoriaQ(string n);
        int ingresarBandejaQ(struct registrosalida registro, string n);
        registrosalida retirarRegistroDeQ(char tipo, string n);

        int ingresarSalida(registrosalida registro, string n);
        int recorrerOE(string n);

        int IngresarReactivo(string nombre, int cantidad, char tipo);
        int ImprimirReactivo(string nombre);

        int retornarContador(string nombre);
};